function gaussElimiation(origin) {
    //origin = array 2d
    //origin = [[5, 2, 1], [3, 1, 4], [1, 1, 3]];
    //origin = [[10, 2, -1], [-3, -6, 2], [1, 5, 5]];
    if (origin == null) {
      alert("Preencha todos os campos!");
      return;
    } else if (isNullMatrix(origin)) {
      alert("A matriz não pode ser nula!");
      return;
    } else if (math.det(origin) == 0) {
      alert("É uma matriz singular. O determinante da matriz é 0");
      return;
    }
  
    let pivot = pivoting(copyMatrix(origin));
  
    if (pivot != null)
    {
      origin = copyMatrix(pivot);
    }
  
    let matrixLU = copyMatrix(origin);
  
    for (let i = 1; i < origin[0].length; i++)
    {
      matrixLU[i][0] = math.round(origin[i][0] / matrixLU[0][0], 3);
    }
  
    let factor = 0;
  
    for (let i = 1; i < origin.length; i++)
    {
      
      for (let j = i; j < origin[i].length; j++)
      {
        factor = 0;
        for (let n = 0; n < i; n++)
        {
          factor += matrixLU[i][n] * matrixLU[n][j];
        }
  
        matrixLU[i][j] = math.round(origin[i][j] - factor, 3);
  
       }
  
      for (let j = i + 1; j < origin.length; j++)
      {
        factor = 0;
        for (let n = 0; n < i; n++)
        {
          factor += matrixLU[j][n] * matrixLU[n][i];
        }
        matrixLU[j][i] = math.round(origin[j][i] - factor, 3); 
      }
  
    }
    
    //MATRIX L
    matrixL = getLUMatrix(matrixLU, "l", matrixLU.length - 2);
    //console.log(matrixL);
    //MATRIX U
    matrixU = getLUMatrix(matrixLU, "u", matrixLU.length - 1);
    //console.log(matrixU);
    
    return {
      l: matrixL,
      u: matrixU
    };
  }
  
