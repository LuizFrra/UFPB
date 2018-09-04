function draw()
{
    var data = []
    const expressao = document.getElementById('eq').value
    const expr = math.compile(expressao)
    const xValores = math.range(-100, 100, 1).toArray()

    const yValores = xValores.map(function (x) 
    {
        return expr.eval({x: x})
    })

    const trace1 = 
    {
        x: xValores,
        y: yValores,
        type: 'scatter'
    }

    data.push(trace1)

    var x0 = Number(document.getElementById('x0').value)
    var x1 = Number(document.getElementById('x1').value)
    const tol = Number(document.getElementById('tol').value)
    const iMax = Number(document.getElementById('epoch').value)

    var i = 2
    var fx1 = expr.eval({x: x0})
    var fx2 = expr.eval({x: x1})

    while ( i <= iMax )
    {
       xk = (x1 - fx1*(x1 - x0))/(fx2 - fx1)
       if( (xk  - x1) < tol )
       {
        var text = "A raiz encontrada foi " + xk + " em " + i + " iterações."
        console.log("Raiz encontrada")
        //Exibe o resultado na página HTML
        document.getElementById("resultado").innerHTML = text
        break
       }
       i += 1
       k = expr.eval({x: xk})

       if(k * fx2 < 0 )
       {
           x0 = x1
           fx1 = fx2
       }
        x1 = x
        fx2 = k
       
    }

    Plotly.newPlot('plot', data)
}

document.getElementById('form').onsubmit = function (event) {
    event.preventDefault()
    draw()
}