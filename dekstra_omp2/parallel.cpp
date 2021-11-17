#include <vector>
#include <omp.h>
float parallel(std::vector<std::vector<float>> a)
{
	float e_time, s_time, f_time;
	int i;
	std::vector<float> r1 = { 0 };
	std::vector<float> p1 = { 0 };
	std::vector<float> p_flag1 = { 0 };
	omp_set_dynamic(0);
	omp_set_num_threads(4);
	s_time = omp_get_wtime();
#pragma omp parallel for
	for (i = 1;i < a.size(); i++)
	{
		r1.push_back(INFINITY);
		p1.push_back(0);
		p_flag1.push_back(1);
	}
#pragma omp parallel private(i)
	{
		 i = 0;
		while (i < a.size())
		{
			if (a[0][i] != 0)
			{
				r1[i] = a[0][i];
			}
			i += 1;
		}}
#pragma omp parallel shared(a) private(i)
	{
		while (p1 != p_flag1)
		{
			int temp = 0;
			float min = INFINITY;
			i = 1;
			while (i < a.size())
			{
				if (r1[i] <= min and p1[i] == 0)
				{
					min = r1[i];
					temp = i;
				}
				i += 1;
			}
			p1[temp] = 1;
			i = 1;
			while (i < a.size() and temp < a.size())
			{
				if (p1[temp] == 1 and i != temp)
				{
					if (a[temp][i] != 0)
					{
						if ((r1[temp] + a[temp][i]) < r1[i])
						{
							r1[i] = r1[temp] + a[temp][i];
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