# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

#Para um f1 = 20, f2=200 e AvMed=200

passo = 1
frequenciaInicial = passo
frequenciaFinal = 200 + passo
frequenciaCorte = 20
AvMed = 200
frequencias = np.arange(frequenciaInicial, frequenciaFinal, passo)

formula = lambda t: (AvMed)/((np.sqrt(1 + np.power(frequenciaCorte/t, 2))) 
                    * (np.sqrt(1 + np.power(t/frequenciaCorte, 2))))

ganhos = formula(frequencias)

plt.plot(ganhos)
plt.show()