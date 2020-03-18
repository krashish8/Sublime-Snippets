int best = 0, sum = 0;
for (int k = 0; k < n; k++)
{
	sum = max(arr[k], sum + arr[k]);
	best = max(sum, best);
}
cout << best;
