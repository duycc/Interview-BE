
/*

（小数，基准元素，大数）。在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。

快速排序思路：
1. 选取第一个数为基准
2. 将比基准小的数交换到前面，比基准大的数交换到后面
3. 对左右区间重复第二步，直到各区间只有一个数

*/

// 递归形式
template <typename T>
void quick_sort_recursive(std::vector<T>& vec, int start, int end)
{
	if (start >= end) return;

	int left = start;
	int right = end;
	T key = vec[left];

	while (left < right) {
		while (left < right && vec[right] >= key)
			right--;
		if (left < right)
			vec[left++] = vec[right];

		while (left < right && vec[left] <= key)
			left++;
		if (left < right)
			vec[right--] = vec[left];
	}

	vec[left] = key;
	quick_sort_recursive(vec, start, left - 1);
	quick_sort_recursive(vec, left + 1, end);
}

// 迭代形式 -> 需要用到栈结构
struct Range{
	int start, end;
	Range(int s = 0, int e = 0)
	{
		start = s;
		end = e;
	}
};

template <typename T>
void quick_sort_iter(std::vector<T>& vec)
{
	std::vector<Range> range(vec.size());

	int p = 0;
	range[p++] = Range(0, vec.size() - 1);
	while (p) {
		Range seq= range[--p];
		if (seq.start >= seq.end) {
			continue;
		}

		T key = vec[seq.end];
		size_t left = seq.start;      
		size_t right = seq.end - 1;
		while (left < right) {
			while (left < right && vec[left] < key) left++;
			while (left < right && vec[right] >= key) right--;
			std::swap(vec[left], vec[right]);
		}

		if (vec[left] >= vec[seq.end]) {
			std::swap(vec[left], vec[seq.end]);
		}
		else {
			left++;
		}

		range[p++] = Range(seq.start, left-1);
		range[p++] = Range(left, seq.end);
	}

	return;
}

