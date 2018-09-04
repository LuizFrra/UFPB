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
    var xp = 0, xn = 0
    var x0 = Number(document.getElementById('x0').value)
    var x1 = Number(document.getElementById('x1').value)
    const tol = Number(document.getElementById('tol').value)
    const iMax = Number(document.getElementById('epoch').value)
    if(expr.eval({x: x0}) > 0 && expr.eval({x: x1}) < 0 )
    {
        xp = x0 
        xn = x1
    }else{
        xp = x1
        xn = x0
    }

    var i  = 1
    while ( i <= iMax)
    {
        var f1 = expr.eval({x: xp})
        var f2 = expr.eval({x: xn})

        var xf = ((xp * f2) - (xn * f1)) / (f2 - f1)
        var fx = expr.eval({x: xf}) 

        var newTrace = {
            x: [xp, xn],
            y: [f1, f2],
            mode: 'lines',
            type: 'scatter'
        }
        data.push(newTrace)
        if( fx > 0){
            xp = xf
        }else{
            xn = xf
        }
        if(math.abs(fx) < tol){
            var text = "A raiz encontrada foi " + xf + " em " + i + " iterações."
            console.log("Raiz encontrada")
            //Exibe o resultado na página HTML
            document.getElementById("resultado").innerHTML = text
            break
        }
        i += 1
    }

    Plotly.newPlot('plot', data)
}

document.getElementById('form').onsubmit = function (event) {
    event.preventDefault()
    draw()
}