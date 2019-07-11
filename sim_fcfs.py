from numpy.random import random
from numpy import log

_rodadas = 9;
_kmin = 100000;
_mi = 1;
_lambda = 0.9;
_FCFS = True;

def exponencial(_rate): 
	uni = random()
	return -log(1.0-uni)/_rate

W_0 = 0.0
R = 0
next_arrival = 0.0

def rodada_fcfs(): 
	global W_0, next_arrival
	T = 0.0
	w_i = 0
	n = 0
	while n < _kmin:
		T += next_arrival
		W_0 = max(0, W_0 - next_arrival)
		w_i = (w_i*n + W_0)/(n+1)
		n += 1
		W_0 += exponencial(1.0)
		next_arrival = exponencial(_lambda)
	print( "Rodada", R, ": E[W]=", w_i, " e E[Nq]=", w_i*n/T, " e T=", T )
	T = 0.0


# main
print( "rodadas=", _rodadas ,"kmin=", _kmin ," lambda=", _lambda )
next_arrival = exponencial(_lambda)
while R <= _rodadas:
	rodada_fcfs()
	R += 1
