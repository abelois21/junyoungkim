#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

bool static greator(char ch1, char ch2) {
	return ch1 > ch2;
}

int solution(string numbers) {
	int answer = 0, upper_bound, max, cur_prime;
	unordered_map<int, bool> isNotPrime;

	// 예상되는 소수 세트 만들기 - 에라토스테네스의 체 이용
	sort(numbers.begin(), numbers.end(), greator);
	max = std::stoi(numbers);
	upper_bound = (int)std::sqrt(max) + 1;  // 에라토스테네스의 체의 가장 큰 소인수 
											// 이 소인수(A)보다 큰 소인수(B)가 존재해도, A보다 작은 소인수 C가 다 걸러냄 
	cur_prime = 2;
	isNotPrime[0] = 1; isNotPrime[1] = 1;
	while (cur_prime <= upper_bound) {    // 처음부터 upper_bound가 2보다 작을 때  
		int previous;
		for (int i = cur_prime * 2; i <= max; i += cur_prime) isNotPrime[i] = 1;

		previous = cur_prime;
		for (int i = cur_prime + 1; i <= upper_bound; i++) {
			if (!isNotPrime[i]) {
				cur_prime = i;
				break;
			}
		}
		if (previous == cur_prime) break;
	}

	unsigned int code = 0;
	unsigned int end_of_code = 0;
	for (int i = 0; i < numbers.size(); i++) 
		end_of_code |= (1 << i);

	// 소수를 조합하여, 위의 prime에 있는지 대조 
	while (code++ != end_of_code) {
		string choosed;
		for (int i = 0; i < numbers.size(); i++)
			if (code & (1 << i))
				choosed += numbers[i];

		// 선택된 수로 순서바꿔 조합하기
		sort(choosed.begin(), choosed.end());
		do {
			int temp = std::stoi(choosed);
			if (!isNotPrime[temp]) {
				answer += 1;
				isNotPrime[temp] = 1;
			}
		} while (std::next_permutation(choosed.begin(), choosed.end()));

	}

	return answer;
}
