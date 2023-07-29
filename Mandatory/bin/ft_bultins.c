#include <stdlib.h>
#include <string.h>
void	ft_bultin(char **arg)
{
	if (!strcmp(arg[0], "export"))
		ft_export(arg);
	

}