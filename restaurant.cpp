#include "main.h"
int MAXSIZE=0;
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(): val(0),left(NULL),right(NULL) {}
	TreeNode(int val) : val(val),left(NULL),right(NULL){}
	TreeNode(int val,TreeNode* left,TreeNode* right) : val(val),left(left),right(right){}
};
typedef struct TreeNode TreeNode;
void addBSTree(TreeNode*& root,int key){
	if(!root) {
		root=new TreeNode(key);
		return;
	}
	if(key<root->val) addBSTree(root->left,key);
	else addBSTree(root->right,key);
}
TreeNode* deleteBSTree(TreeNode*& root,int key){
	if(root==NULL) return NULL;
	if(root->val>key) {root->left=deleteBSTree(root->left,key); return root; }
	else if(root->val<key) {root->right=deleteBSTree(root->right,key); return root; }
	if(root->left==NULL){
		TreeNode* temp=root->right;
		delete root;
		return temp;
	}
	else if(root->right==NULL){
		TreeNode* temp=root->left;
		delete root;
		return temp;
	}
	else{
		TreeNode* temp1=root;
		TreeNode* temp=root->right;
		while(temp->left!=NULL){
			temp1=temp;
			temp=temp->left;
		}
		if(temp1!=root) temp1->left=temp->right;
		else temp1->right=temp->right;
		root->val=temp->val;
		delete temp;
		return root;
	}
}
void post_order(TreeNode* p,vector<int>& a){
	if(p==NULL) return;
	a.push_back(p->val);
	post_order(p->left,a);
	post_order(p->right,a);
}
class hashtable{
public:
	hashtable():arr(MAXSIZE+1) {}
	void insertresturant(int result){
		int id=result%MAXSIZE+1;
		arr[id].inserttree(result);
	}
	void removeresturant(){
		for(int i=1;i<=MAXSIZE;i++) arr[i].removetree();
	}
    void print_tainum(int num){
        arr[num].print();
    }
	class customer{
	private:
		queue<int> customeTime;
		TreeNode* root;
	public:
		customer():root(NULL) {}
		~customer(){
			while(!customeTime.empty()){
				root=deleteBSTree(root,customeTime.front());
				customeTime.pop();
			}
		}
        void print_inoder(TreeNode* p){
        if(p==NULL) return;
	    print_inoder(p->left);
	    cout<<p->val<<endl;
	    print_inoder(p->right);
        }
        void print(){
            print_inoder(root);
        }
		void inserttree(int result){
			customeTime.push(result);
			addBSTree(root,result);
		}
		unsigned long long solve(vector<int> node,vector<vector<long long>> a)
    {
        if(node.size()<=2) return 1;
        vector<int> lf,rt;
        for(int i=1;i<node.size();i++)
        {
            if(node[i]<node[0]) lf.push_back(node[i]);
            else if(node[i]>=node[0]) rt.push_back(node[i]);
        }
        return (((solve(lf,a))%MAXSIZE*(solve(rt,a))%MAXSIZE)%MAXSIZE*a[node.size()-1][lf.size()])%MAXSIZE;
    }
	void removetree(){
		vector<int> ans;
		post_order(root,ans);
		unsigned long long dapan=0;
		if(ans.size()<=2) dapan=1;
		else{
		vector<vector<long long>> F(ans.size()+1);
		for(int i=0;i<=F.size()-1;i++)
        	{
           		F[i]=vector<long long>(i+1,1);
            for(int j=1;j<i;j++) F[i][j]=(F[i-1][j]+F[i-1][j-1])%MAXSIZE;
		}
        dapan=solve(ans,F);
		}
		dapan%=MAXSIZE;
			while(dapan--&&!customeTime.empty()){
			root=deleteBSTree(root,customeTime.front());
			customeTime.pop();
			}
		}
	};
    private:
	vector<customer> arr;
};
hashtable Gojo_res;
class MinHeap_Sakuna {
public:
    MinHeap_Sakuna() {
		seat_min=0;
	}
    void addGuests(int result,int numGuests=1) {
        int seatNumber=result%MAXSIZE+1;
        if (seatCount.find(seatNumber) == seatCount.end()) {
            seatCount[seatNumber] = 0;
            heap.push_back(seatNumber);
            push_heap(heap.begin(), heap.end(), [this](int seat1, int seat2) {
        return compare(seat1, seat2);
    });
        }
          seatCount[seatNumber] += numGuests;
		vector<int>::iterator it;
		it=find(heap.begin(), heap.end(), seatNumber);
		timecustom.push_back({result,seatNumber});
		if(seat_min==0||(seatCount[timecustom[seat_min-1].second]>seatCount[seatNumber])) seat_min =timecustom.size();
        change_current=seatNumber;
		if(it-heap.begin()==heap.size()-1) reheapUp(heap.size()-1);
		else reheapDown(it-heap.begin());
		// for(int i=heap.size()-1; i >= heap.size()/2; i--) {
        // reheapUp(i);}
    }
    void removeGuests(int numGuests) {
        for(int i=0;i<numGuests;i++){
			if(heap.size()==0) return;
        int seatNumber=khuvucxoa();
        if (seatCount.find(seatNumber) == seatCount.end() ) {
            return;
        }
        remove_timecustom(numGuests,seatNumber);
        if(seatCount[seatNumber] < numGuests) { 
			seatCount.erase(seatNumber);}
       else seatCount[seatNumber] -= numGuests;
        reheapDown(seatNumber);
        change_current=seatNumber;
    }
    }
	int khuvucxoa(){
	if(seat_min == change_current){
        int index=heap[0];
        for(int i=1;i<heap.size();i++){
            if(heap[i]==timecustom[seat_min-1].second) continue;
            else{
                if(seatCount[index]>seatCount[heap[i]]) index=heap[i];
                else if(seatCount[index]==seatCount[heap[i]]) if(change_ganday(heap[i],index)) index=heap[i];
            }
        }
        return index;
    }
    else{
        return timecustom[seat_min-1].second;
    }
	}
	void print_seat(int NUM) {
      print_preoder(0,NUM);
    }
    void print_preoder(int i,int NUM) {
        if(i>=heap.size()) return;
        print_last(NUM,heap[i]);
        print_preoder(i*2+1,NUM);
        print_preoder(i*2+2,NUM);
    }
    void print_last(int NUM,int seat){
        for(int i=timecustom.size()-1;i>=0;i--){
             if(NUM==0) break;
            if(timecustom[i].second==seat){
                cout<<timecustom[i].first<<"-"<<timecustom[i].second<<endl;
                NUM--;
            }
        }
    }
private:
    int max_size;
    vector<int> heap;
    unordered_map<int, int> seatCount; 
	vector<pair<int,int>> timecustom;
	int seat_min;
    int change_current;
    void remove_timecustom(int num,int seat){
        for(int i=0;i<timecustom.size();i++) {
            if(num==0) break;
            if(timecustom[i].second==seat){
                cout<<timecustom[i].first<<"-"<<timecustom[i].second<<endl;
                timecustom.erase(timecustom.begin()+i);
                num--;
            }
        }
    }
    bool change_ganday(int seat1,int seat2){
        for(int i=timecustom.size()-1; i>=0; i--){
            if(timecustom[i].second == seat1) return true;
            else if(timecustom[i].second == seat2) return false;
        }
        return false;
    }
    bool compare(int seat1, int seat2) {
        return seatCount[seat1] < seatCount[seat2] || (seatCount[seat1] == seatCount[seat2] && change_ganday(seat1,seat2));
    }
    void reheapUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (compare(heap[index], heap[parentIndex])) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    void reheapDown(int index) {
        while (2 * index + 1 < heap.size()) {
            int childIndex = 2 * index + 1;
            if (childIndex + 1 < heap.size() && compare(heap[childIndex + 1], heap[childIndex])) {
                childIndex++;
            }
            if (compare(heap[childIndex], heap[index])) {
                swap(heap[childIndex], heap[index]);
                index = childIndex;
            } else {
                break;
            }
        }
    }
};
MinHeap_Sakuna Sakuna_res;
void GojoMinHeap(int result){
	Gojo_res.insertresturant(result);
}

void SukunaMinHeap(int result){
    Sakuna_res.addGuests(result);
}
bool areSameCase(char char1, char char2) {
    return (isupper(char1) == isupper(char2)) || (islower(char1) == islower(char2));
}
class HuffmanNode{
    public:
	char data;
	int frequency;
    int height;
	HuffmanNode* pLeft;
	HuffmanNode* pRight;
    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        pLeft = pRight = nullptr;
        this->height=0;
    }
    friend bool operator<(const HuffmanNode& a,const HuffmanNode& b) {
		return a.frequency < b.frequency||(a.frequency==b.frequency&&((a.data<b.data&&areSameCase(a.data,b.data))||(a.data>b.data&&!areSameCase(a.data,b.data))));
	}
   friend bool operator>(const HuffmanNode& a,const HuffmanNode& b) {
		return a.frequency > b.frequency||(a.frequency==b.frequency&&((a.data>b.data&&areSameCase(a.data,b.data))||(a.data<b.data&&!areSameCase(a.data,b.data))));
	}
};
// void rec_print(const HuffmanNode* tree) {
// 		if (tree == nullptr) {
// 			return;
// 		}
// 		if(tree->data!='~') solution << "[" << tree->frequency << "," << tree->data << "]";
// 		else solution << "[" << tree->frequency << "]";
		
// 		if (tree->pLeft != nullptr || tree->pRight != nullptr) {
// 			solution << "(";
// 			rec_print(tree->pLeft);
// 			solution << ",";
// 			rec_print(tree->pRight);
// 			solution << ")";
// 		}
// 	}
	
// 	void print(HuffmanNode* root)
// 	{	
// 		solution << "root : ";rec_print(root);solution << '\n';
// 	}

void assignHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root) {
        huffmanCodes[root->data] = code;
        assignHuffmanCodes(root->pLeft, code + "0", huffmanCodes);
        assignHuffmanCodes(root->pRight, code + "1", huffmanCodes);
    }
}

char giaiMaCaesar(char ch, int shift) {
            bool isUpper = isupper(ch);
            ch = toupper(ch);
            ch = ((ch + shift - 'A' ) % 26) + 'A';

            // Chuyển về chữ cái đúng trường hợp
            if (!isUpper) {
               ch = tolower(ch);
            }
		return ch;
}
int getBalance(HuffmanNode* p){
    if(p==NULL||(p->pLeft==NULL&&p->pRight==NULL)) return 0;
    if(p->pLeft==NULL) return p->pRight->height;
    if(p->pRight==NULL) return p->pLeft->height;
    return p->pLeft->height-p->pRight->height;
}
int binaryToDecimal(const string& binaryString) {
    int decimalNumber = 0;
    for (int i = 0; i < binaryString.length(); ++i) {
        int digit = binaryString[i] - '0';
        decimalNumber += digit * (1 << (binaryString.length() - 1 - i));
    }

    return decimalNumber;
}
HuffmanNode *rotateRight(HuffmanNode *y)  
{  
    HuffmanNode *x = y->pLeft;  
    HuffmanNode *T2 = x->pRight;  
  
    // Perform rotation  
    x->pRight = y;  
    y->pLeft = T2;  
  
    // Update heights  
    y->height = max(y->pLeft->height, 
                    y->pRight->height) + 1;  
    x->height = max(x->pLeft->height, 
                   x->pRight->height) + 1;  
  
    // Return new root  
    return x;  
}  

HuffmanNode *rotateLeft(HuffmanNode *x)  
{  
    HuffmanNode *y = x->pRight;  
    HuffmanNode *T2 = y->pLeft;  
  
    // Perform rotation  
    y->pLeft = x;  
    x->pRight = T2;  
  
    // Update heights  
    x->height = max(x->pLeft->height,     
                    x->pRight->height) + 1;  
    y->height = max(y->pLeft->height,  
                    y->pRight->height) + 1;  
  
    // Return new root  
    return y;  
}  

HuffmanNode* balanceNewNode(HuffmanNode* newNode, int& count) {
    int bal = getBalance(newNode);
    if (bal > 1 && getBalance(newNode->pLeft) > 1) {
        count++;
        return rotateRight(newNode);
    }
    if (bal < -1 && getBalance(newNode->pRight) < -1) {
        count++;
        return rotateLeft(newNode);
    }
    if (bal > 1 && getBalance(newNode->pLeft) < -1) {
        count++;
        rotateLeft(newNode->pLeft);
        return rotateRight(newNode);
    }
    if (bal < -1 && getBalance(newNode->pRight) > 1) {
        count++;
        rotateRight(newNode->pRight);
        return rotateLeft(newNode);
    }
    return newNode;
}
void HAND(HuffmanNode* root);
HuffmanNode* balancetree(HuffmanNode* root, int count=0) {
    if (root == nullptr || count == 1) return root;
    //HAND(root);
    root=balanceNewNode(root, count);
    root->pLeft=balancetree(root->pLeft, count);
    root->pRight=balancetree(root->pRight, count);
    return root;
}
HuffmanNode* laspae(string& name){
	 unordered_map<char,int> a;
     string biendoi=name;
	for(char c:name){a[c]++;}
	if(a.size()<=2) return NULL; 
    unordered_map<char,int> prev;
    for(auto&entryList : a){
        char x = giaiMaCaesar(entryList.first,entryList.second);
        //cout<<entryList.first<<" "<<entryList.second<<" "<<x<<endl;
        prev[x]+=entryList.second;
    }
	vector<pair<char,int>> freq(prev.begin(),prev.end());
	sort(freq.begin(),freq.end(),
	[](const auto& a,const auto& b){
		return a.second > b.second||(a.second==b.second&&((a.first>b.first&&areSameCase(a.first,b.first))||(a.first<b.first&&!areSameCase(a.first,b.first))));
	}
	);
	// 	solution << "freq     : {";
    // for (int i = 0; i <freq.size();i++){
	// 	if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
	// 	else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
	// }
	// 	solution << "}"<<endl;
    for(char&c:biendoi){
        c=giaiMaCaesar(c,a[c]);
    }
	vector<HuffmanNode*> MinHeap1;
	for(int i=0;i<freq.size();i++)
		MinHeap1.push_back(new HuffmanNode(freq[i].first,freq[i].second));
		auto push_heap_lambda = [](const HuffmanNode* a, const HuffmanNode* b) {
        return *a < *b;
    };
	while(MinHeap1.size()>1){
		sort(MinHeap1.begin(), MinHeap1.end(),push_heap_lambda);
		HuffmanNode* left1=MinHeap1[0];
		MinHeap1.erase(MinHeap1.begin());
		HuffmanNode* right1=MinHeap1[0];
		MinHeap1.erase(MinHeap1.begin()); 
       	//solution<<left1->data<<" "<<left1->frequency<<endl<<right1->data<<right1->frequency<<endl;
		HuffmanNode* newNode=new HuffmanNode('~',left1->frequency+right1->frequency);
		newNode->pLeft=left1;
		newNode->pRight=right1;
        newNode->height=max(newNode->pLeft->height,newNode->pRight->height)+1;
        newNode=balancetree(newNode);    
        newNode=balancetree(newNode);     
        newNode=balancetree(newNode);
        MinHeap1.push_back(newNode);
	}
    string ans;
    unordered_map<char, string> huffmanCodes;
    assignHuffmanCodes(MinHeap1[0],"",huffmanCodes);
    for(int i=0;i<biendoi.size();i++) {
        ans=ans+huffmanCodes[biendoi[i]];
    }
    if(ans.size()>=10) ans=ans.substr(ans.size()-10);
    reverse(ans.begin(),ans.end());
	int result=binaryToDecimal(ans);
		// solution << "result = " << result << endl;
		// print(MinHeap1[0]);

	if(result%2==1) GojoMinHeap(result);
	else SukunaMinHeap(result);
	return MinHeap1[0];
}
void KOKUSEN(){
	Gojo_res.removeresturant();
}
void KEITEIKEN(int& num){
	Sakuna_res.removeGuests(num);
}

void HAND(HuffmanNode* root){
	if(root==NULL) return;
    HAND(root->pLeft);
    if(root->data=='~') cout<<root->frequency<<endl;
	else cout<<root->data<<endl;
    HAND(root->pRight);
}
void LIMITLESS(int NUM){
	Gojo_res.print_tainum(NUM);
}
void CLEAVE(int NUM){
	Sakuna_res.print_seat(NUM);
}
void xoa_huffman(HuffmanNode* root){
    if(root==NULL) return;
    xoa_huffman(root->pLeft);
    xoa_huffman(root->pRight);
    delete root;
}
void simulate(string filename)
{
	ifstream ifs(filename);
	string a;
    HuffmanNode* root=NULL;
	while(getline(ifs,a)){
		istringstream iss(a);
		string str;
		iss >> str;
		int value;
        cout<<str<<endl;
		if(str=="MAXSIZE") iss>>MAXSIZE;
        else if(str=="LAPSE"){
            iss>>str;
            xoa_huffman(root);
            root=laspae(str);
        }
		else if(str=="KOKUSEN"){
            KOKUSEN();
        }
        else if(str=="KEITEIKEN"){
            iss>>value;
            KEITEIKEN(value);
        }
        else if(str=="HAND"){
            HAND(root);
        }
        else if(str=="LIMITLESS"){
            iss>>value;
            LIMITLESS(value);
        }
        else if(str=="CLEAVE"){
            iss>>value;
            CLEAVE(value);
        }
	}
	ifs.close();
	return;
}