// Variáveis globais
let dadosCarros = [];
let paginaAtual = 1;
const resultadosPorPagina = 50;
let colunaOrdenacao = null;
let direcaoOrdenacao = 1; // 1 = crescente, -1 = decrescente

// Google Charts
google.charts.load('current', { packages: ['corechart'] });
google.charts.setOnLoadCallback(carregarDados);

function carregarDados() {
    fetch('carros.json')
        .then(response => {
            if (!response.ok) throw new Error('Erro ao carregar dados: ' + response.statusText);
            return response.json();
        })
        .then(dados => {
            dadosCarros = dados;
            init(dadosCarros);
        })
        .catch(error => console.error('Erro:', error));
}

// Seletores
const filterMarca = document.getElementById('filter-marca');
const filterLitragem = document.getElementById('filter-litragem');
const filterAno = document.getElementById('filter-ano');
const filterCombustivel = document.getElementById('filter-combustivel');
const filterCambio = document.getElementById('filter-cambio');

const tabelaCorpo = document.querySelector('#tabela-carros tbody');
const indicadorPrecoMedio = document.getElementById('indicador-preco-medio').querySelector('p');
const indicadorQuantidadeMarcas = document.getElementById('indicador-quantidade-marcas').querySelector('p');
const btnAnterior = document.getElementById('btn-anterior');
const btnProximo = document.getElementById('btn-proximo');

function init(dadosCarros) {
    popularFiltros(dadosCarros);
    atualizarDashboard(dadosCarros);

    const ths = document.querySelectorAll('#tabela-carros thead th');
    ths.forEach(th => {
        th.addEventListener('click', () => {
            const coluna = th.getAttribute('data-col');

            ths.forEach(otherTh => {
                if (otherTh !== th) {
                    otherTh.classList.remove('sorted-asc', 'sorted-desc');
                }
            });

            if (colunaOrdenacao === coluna) {
                direcaoOrdenacao = -direcaoOrdenacao;
            } else {
                colunaOrdenacao = coluna;
                direcaoOrdenacao = 1;
            }

            if (direcaoOrdenacao === 1) {
                th.classList.add('sorted-asc');
                th.classList.remove('sorted-desc');
            } else {
                th.classList.add('sorted-desc');
                th.classList.remove('sorted-asc');
            }

            paginaAtual = 1; // resetar para primeira página
            atualizarDashboard(dadosCarros);
        });
    });

    // Eventos para filtros
    [filterMarca, filterLitragem, filterAno, filterCombustivel, filterCambio].forEach(filtro => {
        filtro.addEventListener('change', () => {
            paginaAtual = 1;
            atualizarDashboard(dadosCarros);
        });
    });

    btnAnterior.addEventListener('click', () => mudarPagina(-1));
    btnProximo.addEventListener('click', () => mudarPagina(1));
}

function ordenarDados(dados, coluna, direcao) {
    return [...dados].sort((a, b) => {
        let valA = a[coluna];
        let valB = b[coluna];

        if (valA == null) valA = '';
        if (valB == null) valB = '';

        if (typeof valA === 'string') valA = valA.toLowerCase();
        if (typeof valB === 'string') valB = valB.toLowerCase();

        if (valA < valB) return -1 * direcao;
        if (valA > valB) return 1 * direcao;
        return 0;
    });
}

function mudarPagina(direcao) {
    paginaAtual += direcao;
    if (paginaAtual < 1) paginaAtual = 1;
    atualizarDashboard(dadosCarros);
}

function popularFiltros(dadosCarros) {
    popularFiltro(filterMarca, [...new Set(dadosCarros.map(c => c.nome_marca))]);
    popularFiltro(filterLitragem, [...new Set(dadosCarros.map(c => c.litros))].sort((a, b) => a - b), v => v + " L");
    popularFiltro(filterAno, [...new Set(dadosCarros.map(c => c.ano))].sort((a, b) => a - b));
    popularFiltro(filterCombustivel, [...new Set(dadosCarros.map(c => c.tipo_combustivel))]);
    popularFiltro(filterCambio, [...new Set(dadosCarros.map(c => c.tipo_cambio))]);
}

function popularFiltro(selectElem, values, formatFn = v => v) {
    selectElem.innerHTML = "<option value=''>Todos</option>";
    values.forEach(val => {
        const o = document.createElement('option');
        o.value = val;
        o.textContent = formatFn(val);
        selectElem.appendChild(o);
    });
}

function atualizarDashboard(dadosCarros) {
    const filtroAtual = {
        marca: filterMarca.value,
        litros: filterLitragem.value ? parseFloat(filterLitragem.value) : null,
        ano: filterAno.value ? parseInt(filterAno.value) : null,
        combustivel: filterCombustivel.value,
        cambio: filterCambio.value
    };

    let dadosFiltrados = dadosCarros.filter(car => {
        return (!filtroAtual.marca || car.nome_marca === filtroAtual.marca)
            && (!filtroAtual.litros || car.litros === filtroAtual.litros)
            && (!filtroAtual.ano || car.ano === filtroAtual.ano)
            && (!filtroAtual.combustivel || car.tipo_combustivel === filtroAtual.combustivel)
            && (!filtroAtual.cambio || car.tipo_cambio === filtroAtual.cambio);
    });

    if (colunaOrdenacao) {
        dadosFiltrados = ordenarDados(dadosFiltrados, colunaOrdenacao, direcaoOrdenacao);
    }

    const totalResultados = dadosFiltrados.length;
    const totalPaginas = Math.ceil(totalResultados / resultadosPorPagina);
    if (paginaAtual > totalPaginas) paginaAtual = totalPaginas;

    const faixaInicial = (paginaAtual - 1) * resultadosPorPagina + 1;
    const faixaFinal = Math.min(paginaAtual * resultadosPorPagina, totalResultados);

    document.getElementById('faixa-inicial').textContent = faixaInicial;
    document.getElementById('faixa-final').textContent = faixaFinal;
    document.getElementById('total-resultados').textContent = totalResultados;

    btnAnterior.disabled = paginaAtual <= 1;
    btnProximo.disabled = paginaAtual >= totalPaginas;

    atualizarTabela(dadosFiltrados);
    atualizarIndicadores(dadosFiltrados);
    desenharGraficos(dadosFiltrados);
}

function atualizarTabela(dados) {
    tabelaCorpo.innerHTML = '';

    if (dados.length === 0) {
        tabelaCorpo.innerHTML = '<tr><td colspan="10" style="text-align:center; padding:20px;">Nenhum registro encontrado.</td></tr>';
        return;
    }

    const inicio = (paginaAtual - 1) * resultadosPorPagina;
    const fim = inicio + resultadosPorPagina;
    const dadosPaginados = dados.slice(inicio, fim);

    dadosPaginados.forEach(car => {
        const tr = document.createElement('tr');
        tr.innerHTML = `
            <td>${car.nome_marca}</td>
            <td>${car.nome_modelo}</td>
            <td>${car.ano}</td>
            <td>${car.litros.toFixed(1)}</td>
            <td>${car.tipo_combustivel}</td>
            <td>${car.tipo_cambio}</td>
            <td>${car.proprietarios}</td>
            <td>${car.portas}</td>
            <td>${car.quilometragem.toLocaleString('pt-BR')} km</td>
            <td>R$ ${car.preco.toLocaleString('pt-BR', { minimumFractionDigits: 2 })}</td>
        `;
        tabelaCorpo.appendChild(tr);
    });
}

function atualizarIndicadores(dados) {
    if (dados.length === 0) {
        indicadorPrecoMedio.textContent = 'R$ 0,00';
        indicadorQuantidadeMarcas.textContent = '0';
        return;
    }
    const precoMedio = dados.reduce((acc, c) => acc + c.preco, 0) / dados.length;
    indicadorPrecoMedio.textContent = precoMedio.toLocaleString('pt-BR', { style: 'currency', currency: 'BRL' });

    const marcasUnicas = new Set(dados.map(c => c.nome_marca));
    indicadorQuantidadeMarcas.textContent = (dados.length / marcasUnicas.size).toFixed(2);
}

function desenharGraficos(dados) {
    desenharPrecoPorMarca(dados);
    desenharQuantidadePorAno(dados);
    desenharDistribuicaoLitragem(dados);
}

function desenharPrecoPorMarca(dados) {
    const agrupado = dados.reduce((acc, car) => {
        acc[car.nome_marca] = acc[car.nome_marca] || { total: 0, count: 0 };
        acc[car.nome_marca].total += car.preco;
        acc[car.nome_marca].count += 1;
        return acc;
    }, {});

    const dataArray = [['Marca', 'Preço Médio']];
    for (const marca in agrupado) {
        dataArray.push([marca, agrupado[marca].total / agrupado[marca].count]);
    }

    const data = google.visualization.arrayToDataTable(dataArray);
    const options = {
        height: 300,
        legend: { position: 'none' },
        colors: ['#3498db'],
        vAxis: { format: 'currency' },
        chartArea: { width: '70%', height: '70%' }
    };

    const chart = new google.visualization.ColumnChart(document.getElementById('chart-preco-marca'));
    chart.draw(data, options);
}

function desenharQuantidadePorAno(dados) {
    const agrupado = dados.reduce((acc, car) => {
        acc[car.ano] = (acc[car.ano] || 0) + 1;
        return acc;
    }, {});

    const dataArray = [['Ano', 'Quantidade']];
    Object.keys(agrupado).sort().forEach(ano => dataArray.push([ano, agrupado[ano]]));

    const data = google.visualization.arrayToDataTable(dataArray);
    const options = {
        height: 300,
        legend: { position: 'none' },
        colors: ['#9b59b6'],
        chartArea: { width: '70%', height: '70%' }
    };

    const chart = new google.visualization.LineChart(document.getElementById('chart-quantidade-ano'));
    chart.draw(data, options);
}

function desenharDistribuicaoLitragem(dados) {
    const agrupado = dados.reduce((acc, car) => {
        acc[car.litros] = (acc[car.litros] || 0) + 1;
        return acc;
    }, {});

    const dataArray = [['Litragem', 'Quantidade']];
    for (const litro in agrupado) {
        dataArray.push([litro + ' L', agrupado[litro]]);
    }

    const data = google.visualization.arrayToDataTable(dataArray);
    const options = {
        height: 300,
        pieHole: 0.4,
        colors: ['#e67e22', '#d35400', '#f39c12', '#c0392b', '#2980b9'],
        chartArea: { width: '90%', height: '80%' }
    };

    const chart = new google.visualization.PieChart(document.getElementById('chart-litragem'));
    chart.draw(data, options);
}

window.addEventListener('resize', () => atualizarDashboard(dadosCarros));
