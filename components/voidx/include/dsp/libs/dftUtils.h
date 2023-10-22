/*
 * dftUtils.h
 *
 *  Created on: 12 gen 2021
 *      Author: Michele
 */

#ifndef KORE_PROFILER_DFTUTILS_H_
#define KORE_PROFILER_DFTUTILS_H_

#define MAX_N_DFT_UTILS				16384
//NB tutto lavora con ipotesi N <= 16384

//convoluzione tra due IR reali di lunghezza N, risultato troncato a N (N < 8192)
void fft_convolute(float * real_1, float * real_2, unsigned int N, float * result);
//calcolo spettro (parte destra) di un segnale lungo N (pari >= 4), se absDft != 0 calcola abs
void getSpectrum(float * signal, float * spectrum, float N, unsigned int absDft);
//ritorna 4 se N è potenza di 4, altrimenti 2
unsigned int getFtButterflySize(int N);
//bandwidth va da f/bw a f*bw, il metodo ritorna bw
float filterQToBandwidth(float Q);
//ritorna power in banda compresa tra fMin e fMax: N è dimensione spettro (visto simmetrico), ma lui considera fino a N/2
float getPowerInBand(float * spectrum, unsigned int N, float fMin, float fMax);


#endif /* KORE_PROFILER_DFTUTILS_H_ */
