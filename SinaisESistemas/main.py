#!/usr/bin/python3

import sys
import cv2 as cv
import numpy as np
import random

# def print_help():
#     print('''
#     This program demonstrated the use of the discrete Fourier transform (DFT).
#     The dft of an image is taken and it's power spectrum is displayed.
#     Usage:
#     discrete_fourier_transform.py [image_name -- default lena.jpg]''')

def MeanSquaredError(matrizA, matrizB):
    return np.square(np.subtract(matrizA, matrizB)).mean()

def NormalizaMatriz(matriz):
    Max, Min = matriz.max(), matriz.min()
    return (matriz - Min)/(Max - Min)

def getRealImaginary(imagem):
    I = cv.imread(imagem, cv.IMREAD_GRAYSCALE)
    if I is None:
        print('Error opening image')
        return -1
    
    rows, cols = I.shape
    m = cv.getOptimalDFTSize( rows )
    n = cv.getOptimalDFTSize( cols )
    padded = cv.copyMakeBorder(I, 0, m - rows, 0, n - cols, cv.BORDER_CONSTANT, value=[0, 0, 0])
    # padded = cv.copyMakeBorder(I, 0, 4, 0, 4, cv.BORDER_CONSTANT, value=[0, 0, 0])
    planes = [np.float32(padded), np.zeros(padded.shape, np.float32)]
    complexI = cv.merge(planes)         # Add to the expanded another plane with zeros
    
    cv.dft(complexI, complexI)         # this way the result may fit in the source matrix
    
    cv.split(complexI, planes)                   # planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    return planes

def calculate():
    acerto = 0
    randomNumber = random.randint(1, 10)
    for x in range (1, 41):
        lista = list()
        print("orl_faces/s" + str(x) + "/" + str(randomNumber) + ".pgm")
        mainImage = getRealImaginary(imagem = "orl_faces/s" + str(x) + "/" + str(randomNumber) + ".pgm")
        mainReal = NormalizaMatriz(mainImage[0])
        mainImaginary = NormalizaMatriz(mainImage[1]) 
        for i in range(1, 41):
            listaTwo = list()
            for j in range (1, 11):
                if(j == randomNumber):
                    break
                secondImg = getRealImaginary(imagem = "orl_faces/s" + str(i) + "/" + str(j) + ".pgm")
                mse = MeanSquaredError(mainReal, NormalizaMatriz(secondImg[0]))
                #mse =  MeanSquaredError(mainReal, NormalizaMatriz(secondImg[1]))
                #mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[1]))
                #mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[0]))
                #mse =  MeanSquaredError(np.add(mainReal, mainImaginary), np.add(secondImg[0], secondImg[1]))
                listaTwo.append(mse)
            lista.append(listaTwo)
        menorLinha = 0
        menorValor = 2
        contador = 0
        for linha in lista:
            for coluna in linha:
                if coluna < menorValor :
                    menorValor = coluna
                    menorLinha = contador
            contador = contador + 1
        print(menorLinha)
        if(x == menorLinha):
            acerto = ((acerto + 1)/40) * 100
    print(acerto)

def ModoLuiz(randomNumber):
    #randomNumber = random.randint(1, 10)
    lista = list()
    for x in range(1, 41):
        #print("orl_faces/s" + str(x) + "/" + str(randomNumber) + ".pgm")
        mainImage = getRealImaginary(imagem = "orl_faces/s" + str(x) + "/" + str(randomNumber) + ".pgm")
        mainReal = NormalizaMatriz(mainImage[0])
        mainImaginary = NormalizaMatriz(mainImage[1])
        menorMseCount = 0
        menorMse = 2
        contador = 1
        for i in range(1, 11):
            #print("orl_faces/s" + str(x) + "/" + str(i) + ".pgm")
            if(i != randomNumber):
                secondImg = getRealImaginary(imagem = "orl_faces/s" + str(x) + "/" + str(i) + ".pgm")
                #mse = MeanSquaredError(mainReal, NormalizaMatriz(secondImg[0]))
                #mse =  MeanSquaredError(mainReal, NormalizaMatriz(secondImg[1]))
                mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[1]))
                #mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[0]))
                #mse =  MeanSquaredError(np.add(mainReal, mainImaginary), np.add(secondImg[0], secondImg[1]))
                if(mse < menorMse):
                    menorMse = mse
                    menorMseCount = contador
                contador = contador + 1
        lista.append(menorMseCount)
    
    return lista

def compara(lista, randomNumber):
    acerto = 0
    for x in range(1, 41):
        mainImage = getRealImaginary(imagem = "orl_faces/s" + str(x) + "/" + str(randomNumber) + ".pgm")
        mainReal = NormalizaMatriz(mainImage[0])
        mainImaginary = NormalizaMatriz(mainImage[1])
        mseMenor = 2
        contador = 1
        mseMenorCount = 0
        for j in range(1, 41):
            #print("orl_faces/s" + str(j) + "/" + str(lista[j]) + ".pgm")
            secondImg = getRealImaginary(imagem = "orl_faces/s" + str(j) + "/" + str(lista[j - 1]) + ".pgm")
            #mse = MeanSquaredError(mainReal, NormalizaMatriz(secondImg[0]))
            #mse =  MeanSquaredError(mainReal, NormalizaMatriz(secondImg[1]))
            mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[1]))
            #mse =  MeanSquaredError(mainImaginary, NormalizaMatriz(secondImg[0]))
            #mse =  MeanSquaredError(np.add(mainReal, mainImaginary), np.add(secondImg[0], secondImg[1]))
            if(mse < mseMenor):
                mseMenor = mse
                mseMenorCount = contador
            contador = contador + 1
        if(x == mseMenorCount):
            print("A imgem " + str(x) + "bateu com o " + str(mseMenorCount))
            acerto = (acerto + 1)
    
    return (acerto/40)*100
def main(argv):
    
    #ImageOne = getRealImaginary(imagem = "orl_faces/s1/1.pgm")
    #ImageTwo = getRealImaginary(imagem = "orl_faces/s1/2.pgm")
    
    #RealPlaneOne = NormalizaMatriz(ImageOne[0])
    #ImaginaryPlaneOne = NormalizaMatriz(ImageOne[1])
    
    #RealPlaneTwo = NormalizaMatriz(ImageTwo[0])
    #ImaginaryPlaneTwo = NormalizaMatriz(ImageTwo[1])

    #print(MeanSquaredError(RealPlaneOne, RealPlaneTwo))
    #print(MeanSquaredError(ImaginaryPlaneOne, ImaginaryPlaneTwo))
    #print(MeanSquaredError(ImaginaryPlaneOne, RealPlaneTwo))
    #print(MeanSquaredError(RealPlaneOne, ImaginaryPlaneTwo))
    #print(MeanSquaredError(np.add(RealPlaneOne, ImaginaryPlaneOne), np.add(RealPlaneTwo, ImaginaryPlaneTwo)))
    #calculate()
    randomNumber = random.randint(1 , 10)
    lista = ModoLuiz(randomNumber)
    print(lista)
    print(compara(lista, randomNumber))
    #print("Real\n")
    #print(NormalizaMatriz(planes[0]))

    #print("\nImaginario\n")
    #print(NormalizaMatriz(planes[1]))


if __name__ == "__main__":
    main(sys.argv[1:])