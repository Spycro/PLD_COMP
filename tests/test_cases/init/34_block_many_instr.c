int main() {
	{
		int i = 0;
		int j = 1;
		int k = 1;
		i = j+k;
		j=i+i;
		k=i+i+j+j+k+1;
		i=0;
		j=0;
	}
	return k;
}

