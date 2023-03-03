#include "word_ladder.h"
#include "fstream"
#include "queue"
#include "unordered_map"
#include "iostream"

// a helper recursive function to gain the complete path from start to the end.
void generate_path (
    std::vector<std::vector<std::string>> &ans,
    const std::string &word,
    std::unordered_map<std::string, std::unordered_set<std::string>> &source,
    std::vector<std::string> &path
) {
    if (source[word].empty()) {
        // reach the end, i.e. the start.
        // reverse the path and add it to ans.
        ans.push_back({path.rbegin(), path.rend()});
        return;
    }
    for (const std::string &parent : source[word]) {
        // get all parent words and call this function again
        path.push_back(parent);
        generate_path(ans, parent, source, path);
        path.pop_back();
    }
}

// a helper function for sort the path in  in lexicographical (alphabetical)
bool compare_rule(std::vector<std::string> v1, std::vector<std::string> v2) {
    if (v1 == v2) 
        return false;
    for (unsigned long i = 0; i < v1.size(); i++) {
        if (v1[i] == v2[i]) 
            continue;
        if (v1[i].compare(v2[i]) < 0) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

// read words line by line from a file
auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	std::string curr;
    std::ifstream file(path);
    std::unordered_set<std::string> dict;
    while (getline(file, curr)) {
        dict.insert(curr);
    }
    file.close();
	return dict;
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
    // todo!!!
    // can imporve the performance by using bfs from both sides. approximately double the speed.
	std::vector<std::vector<std::string>> ans;
    std::queue<std::string> q = std::queue<std::string>{{from}};
    // visited records all visited words with the layer they lies. For avoiding cycling
    std::unordered_map<std::string, int> visited = {{from, 0}};
    // source records the relationship between words and their parents
    std::unordered_map<std::string, std::unordered_set<std::string>> source = {{from, {}}};

    int layer = 0;
    const unsigned long wordLen = from.length();
    bool found = false;
    while (!q.empty()) {
        // gain how many words should be gone through in current layer
        unsigned long numEle = q.size();
        layer++;
        for (unsigned long i = 0; i < numEle; i++) {
            const std::string currWord = q.front();
            std::string newWord = currWord;
            q.pop();
            for (unsigned long j = 0; j < wordLen; j++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    newWord[j] = c;
                    if (!lexicon.contains(newWord)) {
                        // doesn't exist. just go next. O(1) check can save time
                        continue;
                    } else {
                        // must exist
                        if (!visited.contains(newWord)) {
                            // not visited before
                            q.push(newWord);
                            source[newWord].insert(currWord);
                            visited[newWord] = layer;
                        } else if (visited[newWord] == layer) {
                            // visited in the same layer
                            source[newWord].insert(currWord);
                        }
                    }
                    if (newWord == to) 
                        found = true;
                }
                newWord = currWord;
            }
        }
        if (found) 
            break;
    }
    // gain complete path
    if (found) {
        std::vector<std::string> path = {to};
        generate_path(ans, to, source, path);
    }
    // sort!
    std::sort(ans.begin(), ans.end(), compare_rule);
    return ans;
}
