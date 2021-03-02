
/*

（有序区，无序区）。在无序区里找一个最小的元素跟在有序区的后面。对数组：比较得多，换得少。

选择排序思路：
1. 在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
2. 从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾
3. 以此类推，直到所有元素均排序完毕

*/

// 选择排序
void selectSort(std::vector<int>& vec)
{
	size_t len = vec.size();
	size_t min;

	for (size_t i{}; i < len - 1; ++i) {
		min = i;
		for (size_t j = i + 1; j < len; j++) {
			if (vec[j] < vec[min]) {
				min = j;
			}
		}
		if (i != min) {
			std::swap(vec[i], vec[min]);
		}
	}

	return;
}

// 模板实现
template<typename T>
void select_sort(std::vector<T>& vec)
{
	size_t len = vec.size();
	size_t min;

	for (size_t i{}; i < len - 1; ++i) {
		min = i;
		for (size_t j = i + 1; j < len; j++) {
			if (vec[j] < vec[min]) {
				min = j;
			}
		}
		if (i != min) {
			std::swap(vec[i], vec[min]);
		}
	}

	return;
}