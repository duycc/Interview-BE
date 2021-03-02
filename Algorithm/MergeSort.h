
// 归并排序：把数据分为两段，从两段中逐个选最小的元素移入新数据段的末尾。可从上到下或从下到上进行。

/**************
	递归版
**************/
template <typename T>
void merge(std::vector<T>& vec, int low, int mid, int high)
{
	int i = low;
	int j = mid + 1;
	int k = 0;
	std::vector<T> tmp(high - low + 1);
	while (i <= mid && j <= high) {
		tmp[k++] = vec[i] < vec[j] ? vec[i++] : vec[j++];
	}
	while (i <= mid) {
		tmp[k++] = vec[i++];
	}
	while (j <= high) {
		tmp[k++] = vec[j++];
	}

	for (i = low, k = 0; i <= high; ++k, ++i) {
		vec[i] = tmp[k];
	}
}

template <typename T>
void merge_sort_recursive(std::vector<T>& vec, int start, int end)
{
	if (start >= end) return;
	int mid = (end - start) / 2 + start;
	merge_sort_recursive(vec, start, mid);
	merge_sort_recursive(vec, mid+1, end);
	
	merge(vec, start, mid, end);
}


/**************
	迭代版
**************/
template <typename T>
void merge_sort_iter(std::vector<T>& vec)
{
	int size = vec.size();
	for (int width = 1; width < size; width *= 2) {
		for (int i{}; i < size; i += 2 * width) {
			int start1st = i;
			int end1st = std::min(start1st + width - 1, size - 1);
			int start2nd = end1st + 1;
			int end2nd = std::min(start1st + 2 * width - 1, size - 1);
			
			std::vector<T> tmp(end2nd - start1st + 1);
			int k = 0;
			while (start1st <= end1st && start2nd <= end2nd) {
				tmp[k++] = vec[start1st] < vec[start2nd] ? vec[start1st++] : vec[start2nd++];
			}
			while (start1st <= end1st) {
				tmp[k++] = vec[start1st++];
			}
			while (start2nd <= end2nd) {
				tmp[k++] = vec[start2nd++];
			}

			for (k = 0; k < (int)tmp.size(); ++k) {
				vec[i+k] = tmp[k];
			}
		}
	}

	return;
}
