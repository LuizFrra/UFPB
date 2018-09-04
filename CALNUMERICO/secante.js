function draw() {
	try{
		//Variável que irá armazenar os conjuntos de pontos cartesianos do gráfico
                var data = []

		//Parte do código que vai plotar a equação que o usuário colocou na entrada.
                //Salva o valor do campo eq em uma variável
                const expressao = document.getElementById('eq').value
                //Compila o valor de uma string para uma expressão JS
                const expr = math.compile(expressao)

                //Define o pontos que serão aplicados na equação
                const xValores = math.range(-100, 100, 1).toArray()
                //Aplica os valores de x definidos acima na equação para descobrir y
                const yValores = xValores.map(function (x) {
                	return expr.eval({x: x})
                })
                                        
                //Monta os pontos da equação que serão aplicados no gráfico
                const trace1 = {
                        x: xValores,
                        y: yValores,
                        type: 'scatter'
                }
                data.push(trace1)

		//Parte do código que implementa o algoritmo do Método da Secante
		//Pega os valores dos formulários HTML e converte de texto para número
                var p0 = Number(document.getElementById('p0').value)
                var p1 = Number(document.getElementById('p1').value)
                const tol = Number(document.getElementById('tol').value)
                const iMax = Number(document.getElementById('iteracoes').value)

		var i = 2;
		while(i <= iMax) {
			//Aplica os valores de p0 e p1 na expressão definida
			var q0 = expr.eval({x: p0})
			var q1 = expr.eval({x: p1})

			//Traça os valores no gráfico
			var newTrace = {
				x: [p0, p1],
				y: [q0, q1],
				mode: 'lines',
				type: 'scatter'
			}
			//Joga o objeto os dados da secante descoberta no vetor data
			//para depois gerar o gráfico
			data.push(newTrace)
			
			//Pega o novo ponto que será utilizado como secante
			var p = ((p1 - p0)/(q1-q0))*(p1-q1)
			//Essa parte aqui é para ajudar a debugar o código, será removida depois
			console.log("Iteracao: " + i + "\np0 = " + p0 + "\np1 = " + p1 + "\np = " + p + "\nq0 = " + q0 + 
				    "\nq1 = " + q1 + "\n|p - p1| = " + math.abs((p - p1)/p))

			//Condição de parada do loop
			if (math.abs((p - p1)/p) < tol) {
				var text = "A raiz encontrada foi " + p + " em " + i + " iterações."
				console.log("Raiz encontrada")
				//Exibe o resultado na página HTML
				document.getElementById("resultado").innerHTML = text
				break
			}

			//Os novos valores que serão aplicados na secante
			p0 = p1
			p1 = p
			i = i + 1
		}
		
		//Plota o gŕafico
                Plotly.newPlot('plot', data)
	}
        catch (err) {
                console.error(err)
                alert(err)
        }
}

//Executa a função quando o usuário apertar no botão
document.getElementById('form').onsubmit = function (event) {
        event.preventDefault()
        draw()
}
