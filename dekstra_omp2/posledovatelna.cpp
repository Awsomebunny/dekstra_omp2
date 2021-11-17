#include <vector>
#include <omp.h>
float posledovatelna(std::vector<std::vector<float>> a)
{
	float e_time, s_time, f_time;
	int i;
	std::vector<float> r = { 0 };
	std::vector<float> p = { 0 };
	std::vector<float> p_flag = { 0 };
	omp_set_dynamic(0);
	omp_set_num_threads(1);
	s_time = omp_get_wtime();
	for (i = 1;i < a.size(); i++)
	{
		r.push_back(INFINITY);
		p.push_back(0);
		p_flag.push_back(1);
	}
	{
		i = 0;
		while (i < a.size())
		{
			if (a[0][i] != 0)
			{
				r[i] = a[0][i];
			}
			i += 1;
		}}
	{
		while (p != p_flag)
		{
			int temp = 0;
			float min = INFINITY;
			i = 1;
			while (i < a.size())
			{
				if (r[i] <= min and p[i] == 0)
				{
					min = r[i];
					temp = i;
				}
				i += 1;
			}
			p[temp] = 1;
			i = 1;
			while (i < a.size() and temp < a.size())
			{
				if (p[temp] == 1 and i != temp)
				{
					if (a[temp][i] != 0)
					{
						if ((r[temp] + a[temp][i]) < r[i])
						{
							r[i] = r[temp] + a[temp][i];
						}
					}
				}
				i += 1;
			}
		}
	}
	f_time = omp_get_wtime();
	e_time = f_time - s_time;
	return e_time;
}