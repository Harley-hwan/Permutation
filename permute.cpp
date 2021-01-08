#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef long long ll;

string str;
ll k;
int cnt[26] = { 0, };
int tcnt[26];
stack<char> s;

void find(ll target, ll len) {
	if (len == 0) { // 다만들었으므로 
		return;
	}
	// 길이 len 을 만들기 위해서 
	string _str = "";
	ll pre = 0;
	for (int i = 0; i < 26; i++) {
		if (tcnt[i]) {
			char ch = (char)(i + 'a');
			// len 의 맨앞을 i + 'a' 로 만들때 나오는 경우의 수 
			tcnt[i] -= 1;
			ll res = 1;
			for (ll j = 1; j < len; j++) {
				res *= j;
			}
			for (ll j = 0; j < 26; j++) {
				if (tcnt[j]) {
					for (ll a = 1; a <= tcnt[j]; a++) {
						res /= a;
					}
				}
			}
			if (res < target) { // 만약 맨앞을 i + 'a' 로 했는데 경우의 수가 target 보다 작다면 맨앞을 i+'a'로 둘수없음
				tcnt[i] += 1; // 뺀거 다시 더해줌
				target -= res; // 건너뜀
			}
			else { // 크면 가능함
				find(target, len - 1);
				s.push(ch);
				break;
			}
		}
	}
	return;
}
int main() {

	/*
	
	길이 n을 알파벳으로 만드는 경우의 수 
	b a n a n a 의 경우
	a = 3 , b= 1 , n = 2이므로
	6! / 3! / 2!/ 1! = 전체 경우의 수입니다.

	이걸 응용해서 풀이한다.
		
	아래에선 factorial 을 매번 구하지만 전처리하여 푼다.

	*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> str >> k;

	for(int i = 0 ; i < str.length() ; i ++){
        cnt[int(str[i] - 'a')] += 1; // 알파벳 개수 세기
    }

	// 전체 경우의 수 구하기
	ll total = 1;
	for (ll i = 1; i <= str.length(); i++) {
		total *= i;
	}
	for (ll i = 0; i < 26; i++) {
		if (cnt[i]) {
			for (ll j = 1; j <= (ll)cnt[i]; j++) {
				total /= j;
			}
		}
	}
	//cout << "전체 경우 : " << total <<"\n";
	// 전체 경우의 수
	// 원래의 문자열이 몇번째 속하는지 찾아야함
	for (int i = 0; i < 26; i++) {
		tcnt[i] = cnt[i];
	}
	ll o_k = 0; // 원래 문자열이 몇번째 속해있는지
	ll len = str.length();
	int idx = 1;
	for(int q = 0 ; q  < str.length() ; q++){
		char ch = str[q];
		// 다른 알파벳이라면? 해당 알파벳말고 다른것들이 왔을때 경우의수를 전부 구해서 o_k에 더해줘야함
	
		// ch 를 고정시키고 나머지 len - 1 자리를 채우는 경우 

		ll psum = 0;
		for (ll i = 0; i < ll(ch - 'a'); i++) { // 현재 ch 보다 앞선 알파벳들로 경우의수 셈
			if (tcnt[i]) {
				// i를 맨앞에 둿을때 나머지로 만들수있는 경우의수 구함
				ll tres = 1;
				for (ll a = 1; a <= len - 1; a++) { // (len-1)!
					tres *= a;
				}
				// 나머지 tcnt[i] ! 로 나눔
				tcnt[i] -= 1;
				for (int a = 0; a < 26; a++) {
					if (tcnt[a]) {
						for (ll b = 1; b <= tcnt[a]; b++) { //(len-1)! / tcnt[a]!
							tres /= b;
						}
					}
				}
				psum += tres;
				tcnt[i] += 1;
			}
		}
		tcnt[ll(ch - 'a')] -= 1;
		o_k += psum;
		len -= 1;
		idx += 1;
	}
	o_k += 1; // 원래의 문자열은 o_k 번째 사전순에 위치했다
	//cout << "원래 문자열 위치 : " << o_k <<"\n"; // banana의 경우 35
	if (o_k - k < 0) { // 만약에 범위를 넘어가는경우
		cout << "none\n";
	}
	else {
		// 범위를 넘어가지 않으므로 o_k - k 번째 o_k + k 번째 단어를 찾자
		for (int i = 0; i < 26; i++) {
			tcnt[i] = cnt[i];
		}
		find(o_k - k, str.length());
		while (!s.empty()) {
			cout << s.top();
			s.pop();
		}
		cout << "\n";
	}

	if (o_k + k > total) {
		cout << "none\n";
	}
	else{
		for (int i = 0; i < 26; i++) {
			tcnt[i] = cnt[i];
		}
		find(o_k + k, str.length());
		while (!s.empty()) {
			cout << s.top();
			s.pop();
		}
		cout << "\n";
	}
}