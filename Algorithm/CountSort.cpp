
/*****************

计数排序：统计小于等于该元素值的元素的个数i，于是该元素就放在目标数组的索引i位（i≥0）。

计数排序基于一个假设，待排序数列的所有数均为整数，且出现在（0，k）的区间之内。
如果 k（待排数组的最大值） 过大则会引起较大的空间复杂度，一般是用来排序 0 到 100 之间的数字的最好的算法，但是它不适合按字母顺序排序人名。
计数排序不是比较排序，排序的速度快于任何比较排序算法。
时间复杂度为 O（n+k），空间复杂度为 O（n+k）

算法的步骤如下：

1. 找出待排序的数组中最大和最小的元素
2. 统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项
3. 对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）
4. 反向填充目标数组：将每个元素 i 放在新数组的第 C[i] 项，每放一个元素就将 C[i] 减去 1

*****************/

void countSort(std::vector<int>& vec)
{
    int min = *std::min_element(vec.begin(), vec.end());
    int max = *std::max_element(vec.begin(), vec.end());

    std::unordered_map<int, int> hashMap(max - min + 1);
    for (int& elem : vec) {
        hashMap[elem]++;
    }

    int k = 0;
    for (int i = min; i <= max; ++i) {
        while (hashMap[i]--) {
            vec[k++] = i;
        }
    }

    return;
}
