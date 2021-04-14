#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

bool static greator(char ch1, char ch2) {
    return ch1 > ch2;
}

int solution(string numbers) 
{
    int answer = 0, upper_bound, cur_prime, pre_prime;
    long long max;
    vector<int> primes;
    
    // 예상되는 소수 세트 만들기 - 에라토스테네스의 체 이용
    sort(numbers.begin(), numbers.end(), greator);
    max = std::stoi(numbers);
    primes = vector<int>(max+1, 1);
    for(long i = 0 ; i <= max ; i++) primes[i] = i;

    upper_bound = (int)std::sqrt(max) + 1;
    cur_prime = 2;
    while(cur_prime < upper_bound) {
        for(long long i = cur_prime*2 ; i < max ; i += cur_prime) primes[i] = 0;
       
	pre_prime = cur_prime;
	// find next left most prime
	for(auto it = primes.begin() ; it != primes.end() ; it++) {
	    if(*it >= cur_prime+1) {
		cur_prime = *it;
		break;
	    }
	}
	if(pre_prime == cur_prime) break;
    }
    
    sort(numbers.begin(), numbers.end());

    vector<bool> digits(numbers.length(), 0);
    for(int i = 0 ; i < numbers.length() ; i++) {
	digits[i] = 1;
	do {
	    string t_str;
	    for(int j = 0 ; j < digits.size() ; j++) 
		if(digits[j]) t_str += numbers[j];
	    
	    sort(t_str.begin(), t_str.end());

	    do {
		if(primes[std::stoi(t_str)] != 0) {
		    answer += 1;
		    primes[std::stoi(t_str)] = 0;
		}
	    } while(std::next_permutation(t_str.begin(), t_str.end()));
	} while(std::next_permutation(digits.begin(), digits.end()));
    }
    
    
/*    // 내가 만든 permutation 함수
//    queue<int> waits;
//    unordered_map<int, bool> isPrime;
// n번째 성공적으로 생성 -> n+1번째에도 생성 가능한가?
    for(int i = 1 ; i <= numbers.size() ; i++) {
        string t_str;
        int idx = 0;
        vector<int> cnts(i, 0);
        
        while(cnts[0] > length) {
            int n = waits.front();
            waits.pop();
            
            t_str[idx] = n + '0';
            if(idx == i) {
                tmp = stoi(t_str);
                if(isPrime[tmp]) {
                    isPrime[tmp] = 0;
                    answer += 1;
                }  
                waits.push(n);
            }
            else {
                idx += 1;
            }
            cnts[idx] += 1;
            
            while(cnts[idx] == length - idx) {
                cnts[idx] = 0;
                idx -= 1;
                waits.push(t_str[idx]);
            }
        }
        
    }
*/    
    return answer;
}

int main (int argc, char** argv) 
{
    string s("12345678");
    cout << solution(s);
    return 0;
}
