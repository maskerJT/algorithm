#pragma once
#include<iostream>
#include<vector>
#include<list>

using namespace std;

void display(vector<int>nums) {
	for (auto iter : nums)cout << iter << " ";
}

void insertSort(vector<int>nums) {
	for (int i = 1; i < nums.size(); i++) {
		for (int j = i-1; j >=0; j--) {
			if (nums[j + 1] < nums[j])swap(nums[j + 1], nums[j]);
			else break;
		}
	}
	display(nums);
}

void bubbleSort(vector<int>nums) {
	for (int i = 0; i < nums.size(); i++) {
		bool stop = true;
		for (int j = nums.size() - 2; j >= i; j--) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
				stop = false;
			}
		}
		if (stop)break;
	}
	display(nums);
}

void shellSort(vector<int>nums) {
	for (int gap = nums.size() / 2; gap > 0;gap/=2) {
		/*for (int i = nums.size() - 1; i >= 0;i--) {
			for (int j = i - gap; j >= 0; j-=gap) {
				if (nums[j] > nums[j + gap])swap(nums[j],nums[j+gap]);
			}
		}*/
		for (int i = gap; i < nums.size(); i++) {
			for (int j = i - gap; j >= 0; j--) {
				if (nums[j] > nums[j + gap])swap(nums[j], nums[j + gap]);
				else break;
			}
		}
	}
	display(nums);
}

void merge(vector<int>&nums,int left,int right) {
	if (left == right)return;
	if (left + 1 == right && nums[left] > nums[right]) {
		swap(nums[left], nums[right]);
		return;
	}
	int mid = (left + right) / 2;
	merge(nums,left,mid);
	merge(nums,mid+1,right);
	vector<int>temp;
	int i = left; int j = mid + 1;
	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {
			temp.push_back(nums[i++]);
		}else  temp.push_back(nums[j++]);
	}
	while (i <= mid)temp.push_back(nums[i++]);
	while (j <= right)temp.push_back(nums[j++]);
	for (int i = left; i <= right; i++)nums[i] = temp[i - left];
}

void mergeSort(vector<int>nums) {
	if (nums.size() < 2)return;
	merge(nums,0,nums.size()-1);
	display(nums);
}


void quickSort(vector<int>&nums,int left,int right) {
	if (left < right) {
		int i = left + 1;
		int j = right;
		while (true) {
			while (i <= j && nums[i] <= nums[left])i++;
			while (i <= j && nums[j] >= nums[left])j--;
			if (i >= j)break;
			swap(nums[i],nums[j]);
		}
		swap(nums[left],nums[j]);
		quickSort(nums,left,j-1);
		quickSort(nums,j+1,right);
	}
}

void downAdjust(vector<int>&nums,int endindex,int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int maxindex = index;
	if (left <= endindex && nums[left] > nums[index])maxindex = left;
	if (right <= endindex && nums[right] > nums[maxindex])maxindex = right;
	if (maxindex != index) {
		swap(nums[maxindex],nums[index]);
		downAdjust(nums,endindex,maxindex);
	}
}

void heapSort(vector<int>nums) {
	int n = nums.size();
	for (int i = n/2-1; i >= 0; i--) {
		downAdjust(nums,n-1,i);
	}
	for (int i = n - 1; i >= 0; i--) {
		swap(nums[i],nums[0]);
		downAdjust(nums,i-1,0);
	}
	display(nums);
}

void countSort(vector<int>nums) {
	int minValue = INT_MAX;
	int maxValue = INT_MIN;
	for (auto iter : nums) {
		if (iter > maxValue)maxValue = iter;
		if (iter < minValue)minValue = iter;
	}
	if (maxValue == minValue)return;
	vector<int>count(maxValue - minValue + 1, 0);
	for (auto iter : nums) {
		count[iter - minValue]++;
	}
	int k = 0;
	for (int i = 0; i < count.size(); i++) {
		while (count[i]--) {
			nums[k++] = i + minValue;
		}
	}
	display(nums);
}

void bucketSort(vector<int>nums) {
	vector<void*>b;
	vector<list<int>>bone(5);
	for (auto iter : nums) {
		bone[iter % 5].push_back(iter);
	}
	int index = 0;
	for (auto iter : bone) {
		iter.sort();
		for (auto item : iter) {
			nums[index++] = item;
		}
	}
	display(nums);
}
void radixSort(vector<int>nums) {
	int minval = INT_MAX;
	int maxval = INT_MIN;
	for (auto iter : nums) {
		if (iter > maxval)maxval = iter;
		if (iter < minval)minval = iter;
	}
	if (minval < 0) {
		for (auto& iter : nums)iter -= minval;
		maxval -= minval;
	}
	int pos = 1;
	while (maxval / (int)pow(10, pos))pos++;
	vector<list<int>>bones(10);
	for (int i = 0; i < pos; i++) {
		int index = 0;
		for (int iter : nums) {
			bones[iter /(int)pow(10, i) % 10].push_back(iter);
		}
		for (auto &mylist : bones) {
			for (auto iter : mylist) {
				nums[index++] = iter;
			}
			mylist.clear();
		}
	}
	if (minval < 0) {
		for (auto& iter : nums)iter += minval;
	}
	display(nums);
}
