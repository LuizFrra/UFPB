function underIndex(letter, index) {
    /*
      Retorna a letra os texto secundário subscrito
      Params:
        letter: texto principal
        index: texto secundário
    */
    return letter + "_{" + index + "}";
  }

function checkPivoting(matrix){
    /*
      Verifica qual linha da matriz precisa ser pivoteada
      Params:
        matrix: matriz
    */
    for (let i = 0; i < matrix.length; i++) {
      if (matrix[i][i] == 0) {
        return i;
      }
    }
  
    return -1;
}


function isNullMatrix(matrix) {
    /*
      Verifica se a matriz de entrada é nula
      Params:
        matrix: matriz
    */
    let nullMatrix = true;
  
    matrix.forEach(element => {
      element.forEach(cell => {
        //se possuir qualquer valor diferente de 0, a matriz não é nula
        if (cell != 0) {
          nullMatrix = false;
        }
      });
    });
  
    return nullMatrix;
  }

  function pivoting(matrix, bVector = null) {
    /*
      Realiza o pivotemanto em uma matriz e em um vetor
      Params:
        matrix: matriz
        bVector: vetor
    */
    let max = 0;
    let n = 0;
    let column = 0;
  
    //verifica se a matriz ainda precisa de pivoteamento
    //limita a quantidade de iterações pelo tamanho da matriz
    while (checkPivoting(matrix) >= 0 && n < matrix.length) {
      n++;
      column = checkPivoting(matrix);
      max = 0;
  
      //procura a linha que possue o maior valor na mesma coluna em que precisa de pivoteamento
      for (let i = 0; i < matrix.length; i++) {
        if (Math.abs(matrix[i][column]) > Math.abs(matrix[max][column])) {
          max = i;
        }
      }
  
      let copy = copyMatrix(matrix);
  
      matrix[max] = copy[column];
      matrix[column] = copy[max];
  
      //modifica o vetor b associado à matriz
      if (bVector != null) {
        let aux = bVector[column];
        bVector[column] = bVector[max];
        bVector[max] = bVector[column];
      }
    }
  
    return n == 0 ? null : matrix;
  }

  function copyMatrix(matrix) {
    /*
      Faz a cópia dos elementos de uma matriz
      Params:
        matrix: matriz a ser copiada
    */
    let out = [];
  
    matrix.forEach(element => {
      aux = [];
      for (let i = 0; i < element.length; i++) {
        aux.push(element[i]);
      }
      out.push(aux);
    });
  
    return out;
  }



  function getLUMatrix(matrix, type, iteration = 0, label = "") {
    /*
      Retorna a parte Lower ou Upper de uma matriz
      Params:
        - matrix: matriz
        - type: 'l','u','a','g'
        - iteration: interação do algoritmo de separação LU
        - lable: texto dos campos ainda não calculados
    */
  
    let lu = [];
    if (label === "") {
      label = type;
    }
  
    for (let i = 0; i < matrix.length; i++) {
      let aux = [];
      for (let j = 0; j < matrix[i].length; j++) {
        switch (type) {
          case "g":
            if (j <= i) {
              aux.push(underIndex(label, i + 1 + "" + (j + 1)));
            } else {
              aux.push("0");
            }
            break;
          case "a":
            if (j < i) {
              aux.push(underIndex("l", i + 1 + "" + (j + 1)));
            } else {
              aux.push(underIndex("u", i + 1 + "" + (j + 1)));
            }
            break;
          case "l":
            if (j <= i) {
              if (j <= iteration && j < i) {
                aux.push(matrix[i][j]);
              } else if (j == i) {
                aux.push(1);
              } else {
                aux.push(underIndex(label, i + 1 + "" + (j + 1)));
              }
            } else {
              aux.push("0");
            }
            break;
          case "u":
            if (j >= i) {
              if (i <= iteration) {
                aux.push(matrix[i][j]);
              } else {
                aux.push(underIndex(label, i + 1 + "" + (j + 1)));
              }
            } else {
              aux.push("0");
            }
            break;
        }
      }
      lu.push(aux);
    }
  
    return lu;
  }