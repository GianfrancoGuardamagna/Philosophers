#include "philosophers.h"

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if(argc == 5 || argc == 6)
	{
		while(argv[i])
		{
			if(!ft_isint(argv[i]))
				return(0);
			i++;
		}
		return(1);
	}
	return (0);
}