#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int subset_size)
{
	int i;

	printf("{ ");
	for (i = 0; i < subset_size; i++)
	{
		printf("%d ", subset[i]);
	}
	printf("}\n");
}

int ft_sum(int *arr, int size)
{
	int i;
	int sum;

	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += arr[i];
		i++;
	}
	return sum;
}

void solve(int *set, int *subset, int target, int set_size, int subset_size, int index)
{
	int sum;

	sum = ft_sum(subset, subset_size);
	if (sum == target)
	{
		print_subset(subset, subset_size);
		return;
	}
	while (index < set_size)
	{
		if (sum + set[index] <= target)
		{
			subset[subset_size] = set[index];
			solve(set, subset, target, set_size, subset_size + 1, index + 1);
			subset[subset_size] = 0;
		}
		index++;
	}
}


int main(int argc, char *argv[])
{
	int i;
	int *set;
	int *powerset;
	int set_size;
	int target = atoi(argv[1]);

	if (argc < 3)
		return 1;
	set_size = argc - 2;
	set = malloc(set_size * sizeof(int));
	powerset = malloc(set_size * sizeof(int));
	i = 0;
	while (i < set_size)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	solve(set, powerset, target, set_size, 0, 0);
	free(set);
	free(powerset);
	return 0;
}