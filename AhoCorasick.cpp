// Max number of states in the matching machine. 
// Should be equal to the sum of the length of all keywords. 
const int MAXS = 500; 
// Maximum number of characters in input alphabet 
const int MAXC = 26; 
// OUTPUT FUNCTION IS IMPLEMENTED USING out[] 
// Bit i in this mask is one if the word with index i 
// appears when the machine enters this state. 
int out[MAXS]; 
// FAILURE FUNCTION IS IMPLEMENTED USING f[] 
int f[MAXS]; 
// GOTO FUNCTION (OR TRIE) IS IMPLEMENTED USING g[][] 
int g[MAXS][MAXC]; 
// Builds the string matching machine. 
// arr -   array of words. The index of each keyword is important: 
//         "out[state] & (1 << i)" is > 0 if we just found word[i] 
//         in the text. 
// Returns the number of states that the built machine has. 
// States are numbered 0 up to the return value - 1, inclusive. 
int buildMatchingMachine(string arr[], int k) { 
    // Initialize all values in output function as 0. 
    memset(out, 0, sizeof out);   
    // Initialize all values in goto function as -1. 
    memset(g, -1, sizeof g);   
    // Initially, we just have the 0 state 
    int states = 1; 
    // Construct values for goto function, i.e., fill g[][] 
    // This is same as building a Trie for arr[] 
    for (int i = 0; i < k; ++i) { 
        const string &word = arr[i]; 
        int currentState = 0; 
// Insert all characters of current word in arr[] 
        for (int j = 0; j < word.size(); ++j) { 
            int ch = word[j] - 'a'; 
// Allocate a new node (create a new state) if a node for ch doesn't exist. 
            if (g[currentState][ch] == -1) 
                g[currentState][ch] = states++; 
            currentState = g[currentState][ch]; 
        } 
// Add current word in output function 
        out[currentState] |= (1 << i); 
    } 
// For all characters which don't have an edge from root (or state 0) in Trie, add a goto edge to state 0 itself 
    for (int ch = 0; ch < MAXC; ++ch) 
        if (g[0][ch] == -1) 
            g[0][ch] = 0; 
// Now, let's build the failure function 
// Initialize values in fail function 
    memset(f, -1, sizeof f); 
// Failure function is computed in breadth first order using a queue 
    queue<int> q; 
// Iterate over every possible input 
    for (int ch = 0; ch < MAXC; ++ch) { 
        // All nodes of depth 1 have failure function value nas 0. 
        //For example, in above diagram we move to 0 from states 1 and 3. 
        if (g[0][ch] != 0) { 
            f[g[0][ch]] = 0; q.push(g[0][ch]); 
        } 
    } 
// Now queue has states 1 and 3 
    while (q.size()) { 
//Remove the front state from queue 
        int state = q.front(); 
        q.pop(); 
  
// For the removed state, find failure function for all those characters for which goto function is not defined. 
        for (int ch = 0; ch <= MAXC; ++ch) { 
            // If goto function is defined for character 'ch' and 'state' 
            if (g[state][ch] != -1) { 
//Find failure state of removed state 
                int failure = f[state]; 
  
//Find the deepest node labeled by proper suffix of string from root to current state. 
                while (g[failure][ch] == -1) 
                      failure = f[failure]; 
                failure = g[failure][ch]; 
                f[g[state][ch]] = failure; 
                // Merge output values 
                out[g[state][ch]] |= out[failure]; 
                // Insert the next level node (of Trie) in Queue 
                q.push(g[state][ch]); 
            } 
        } 
    } 
    return states; 
} 
// Returns the next state the machine will transition to using goto and failure functions. 
// currentState - The current state of the machine. Must be between 0 and the number of states - 1, inclusive. 
// nextInput - The next character that enters into the machine. 
int findNextState(int currentState, char nextInput) { 
    int answer = currentState; 
    int ch = nextInput - 'a'; 
    // If goto is not defined, use failure function 
    while (g[answer][ch] == -1) 
        answer = f[answer]; 
    return g[answer][ch]; 
} 
// This function finds all occurrences of all array words in text. 
void searchWords(string arr[], int k, string text) { 
    // Preprocess patterns. 
    // Build machine with goto, failure and output functions 
    buildMatchingMachine(arr, k); 
  
    int currentState = 0; 
  
    // Traverse the text through the nuilt machine to find all occurrences of words in arr[] 
    for (int i = 0; i < text.size(); ++i) 
    { 
        currentState = findNextState(currentState, text[i]); 
  
        // If match not found, move to next state 
        if (out[currentState] == 0) 
             continue; 
  
        // Match found, print all matching words of arr[] using output function. 
        for (int j = 0; j < k; ++j) 
        { 
            if (out[currentState] & (1 << j)) 
            { 
                cout << "Word " << arr[j] << " appears from "
                     << i - arr[j].size() + 1 << " to " << i << endl; 
            } 
        } 
    } 
} 
int main() { 
    string arr[] = {"he", "she", "hers", "his"}; 
    string text = "ahishers"; 
    int k = sizeof(arr)/sizeof(arr[0]); 
    searchWords(arr, k, text); 
    return 0; 
} 

// Aho Corasick - wygn
#include<queue>
namespace AHOC {
  const int size = 1000005;
  const int sigma = 52;
  int nxt[size][sigma];
  int mark[size], kmp[size], sl[size];
  int gptr;
  int to(const char x); // zero-based char to int mapper
  void reset() {
    gptr = 0;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < sigma; j++) nxt[i][j] = -1;
      kmp[i] = sl[i] = 0;
      mark[i] = -1;
    }
  }
  void add(const char *str, int x) {
    int ptr = 0, i = 0;
    while (str[i] != '\0') {
      // str: string pattern
      int t = to(str[i]);
      if (nxt[ptr][t] == -1)
        nxt[ptr][t] = ++gptr;
      ptr = nxt[ptr][t];
      i++;
    }
    mark[ptr] = x;  // x-th string
  }
  void build() {
    std::queue<int>q;
    for (int i = 0; i < sigma; i++) {
      if (nxt[0][i] != -1) q.push(nxt[0][i]);
    }
    while (!q.empty()) {
      int siz = q.size();
      for (int i = 0; i < siz; i++) {
        int v = q.front();
        q.pop();
        for (int j = 0; j < sigma; j++) {
          if (nxt[v][j] == -1) continue;
          int k = kmp[v];
          while (k != 0 && nxt[k][j] == -1) k = kmp[k];
          if (nxt[k][j] != -1) k = nxt[k][j];
          kmp[nxt[v][j]] = k;
          sl[nxt[v][j]] = mark[k] != -1 ? k : sl[k];
          q.push(nxt[v][j]);
        }
      }
    }
  }
  // returns number of matched strings and marks 'found' array
  int match(const char *str, int found[]) {
    int j = 0, ret = 0;
    for (int i = 0, v; str[i] != '\0'; i++) {
      v = to(str[i]);
      while (j != 0 && nxt[j][v] == -1) j = kmp[j];
      if (nxt[j][v] != -1) j = nxt[j][v];
      v = j;
      do {
        if (mark[v] != -1 && !found[mark[v]])
          ret += found[mark[v]] = 1;
      } while (v = sl[v]);
    }
    return ret;
  }
}
