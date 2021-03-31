int global = 4;

int fx() { return 0; }

int main() { 
	;
	do {
		global++;
	} while (0);

	{
		int i = 0;
		for (i = 0; i < 5; i++);
	}

	if (0) { } else { }

	while (0) ;

	int calc = 0;

	calc = (calc);
	calc++;
	calc--;
	++calc;
	--calc;
	calc = -calc;
	calc = +calc;
	calc = !calc;
	calc = ~calc;
	calc = (int)calc;
	calc = &calc;
	calc = sizeof(int);
	calc = calc*calc;
	calc = calc/calc;
	calc = calc%calc;
	calc = calc+calc;
	calc = calc-calc;
	calc = calc<<1;
	calc = calc>>1;
	calc = calc<1;
	calc = calc>1;
	calc = calc<=1;
	calc = calc>=1;
	calc = calc==calc;
	calc = calc != calc;
	calc = calc & calc;
	calc = calc ^ calc;
	calc = calc | calc;
	calc = calc && calc;
	calc = calc || calc;
	calc = calc ? calc : calc;
	calc += calc;
	calc -= calc;
	calc *= calc;
	calc /= calc;
	calc %= calc;
	calc <<= calc;
	calc >>= calc;
	calc &= calc;
	calc ^= calc;
	calc |= calc;
	calc, calc;



	return 0;
}
