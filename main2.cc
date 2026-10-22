#include <algorithm>
#include <cctype>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Task 1.1
bool fillFromFile(const std::string& name, std::vector<int>* v) {
  std::ifstream file(name);
  if (!file.is_open()) {
    return false;
  }
  std::vector<int> numbers((std::istream_iterator<int>(file)),
                           std::istream_iterator<int>());
  if (!file.eof() || numbers.empty()) {
    return false;
  }
  *v = numbers;
  return true;
}

// Task 2.6
void addHalves(std::vector<int>* v, std::deque<int>* d) {
  int v_half = v->size() / 2;
  int d_half = d->size() / 2;
  v->insert(v->end(), d->begin(), d->begin() + d_half);
  d->insert(d->begin(), v->rbegin() + d_half, v->rbegin() + d_half + v_half);
}

// Task 3.8
void deleteOdd(std::vector<int>* v) {
  for (std::vector<int>::iterator i = v->begin(); i != v->end(); ++i) {
    i = v->erase(i);
    if (i == v->end()) {
      break;
    }
  }
}

// Task 4.2
bool printOddNumbers(const std::string& name) {
  std::ifstream file(name);
  if (!file.is_open()) {
    return false;
  }
  std::cout << "Numbers with odd positions: ";
  int counter = 0;
  std::remove_copy_if(std::istream_iterator<int>(file),
                      std::istream_iterator<int>(),
                      std::ostream_iterator<int>(std::cout, " "),
                      [&counter](int) {
                        counter++;
                        return counter % 2 == 0;
                      });
  std::cout << "\n";
  return file.eof() && counter > 0;
}

// Task 5.9
void duplicatePositive(std::vector<int>* v, int k) {
  std::vector<int>::iterator pos = std::search_n(
      v->begin(), v->end(), k, 0, [](int x, int value) { return x > value; });
  if (pos == v->end()) {
    return;
  }
  std::vector<int> copy(pos, pos + k);
  v->insert(pos + k, copy.begin(), copy.end());
}

// Task 6.9 (first list)
void duplicateHalf1(std::list<int>* l) {
  std::list<int>::iterator middle = l->begin();
  std::advance(middle, l->size() / 2);
  std::reverse_copy(l->begin(), middle, std::back_inserter(*l));
}

// Task 6.9 (second list)
void duplicateHalf2(std::list<int>* l) {
  std::list<int>::iterator middle = l->begin();
  std::advance(middle, l->size() / 2);
  std::list<int> half(l->begin(), middle);
  l->insert(l->end(), half.rbegin(), half.rend());
}

// Task 7.6
void positiveFirst(std::list<int>* l) {
  std::stable_partition(l->begin(), l->end(), [](int x) { return x > 0; });
}

// Task 8.2
std::deque<std::string> makePairs(const std::list<std::string>& words) {
  std::deque<std::string> d;
  std::adjacent_difference(
      words.begin(), words.end(), std::back_inserter(d),
      [](const std::string& right, const std::string& left) {
        return std::string(1, left[0]) + right[right.size() - 1];
      });
  d.erase(d.begin());
  return d;
}

// Task 9.1
bool isIncluded(const std::vector<int>& v0, const std::vector<int>& v) {
  std::set<int> set0(v0.begin(), v0.end());
  std::set<int> set_v(v.begin(), v.end());
  return std::includes(set_v.begin(), set_v.end(), set0.begin(), set0.end());
}

// Task 10.1
std::map<int, int> countRepeats(const std::vector<int>& v) {
  std::map<int, int> m;
  for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i) {
    m[*i]++;
  }
  return m;
}

}

int main() {
  std::string line;
  bool correct;

  std::cout << "Task 1.1\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::string file_name;
    std::cout << "Enter file name: ";
    std::getline(std::cin, file_name);
    std::vector<int> file_vector;
    if (!fillFromFile(file_name, &file_vector)) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::cout << "Vector: ";
    for (std::vector<int>::iterator i = file_vector.begin();
         i != file_vector.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 2.6\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter elements of vector V (even count): ";
    std::getline(std::cin, line);
    std::istringstream stream1(line);
    std::vector<int> v((std::istream_iterator<int>(stream1)),
                       std::istream_iterator<int>());
    if (!stream1.eof() || v.empty() || v.size() % 2 != 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::cout << "Enter elements of deque D (even count): ";
    std::getline(std::cin, line);
    std::istringstream stream2(line);
    std::deque<int> d((std::istream_iterator<int>(stream2)),
                      std::istream_iterator<int>());
    if (!stream2.eof() || d.empty() || d.size() % 2 != 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    addHalves(&v, &d);
    std::cout << "Vector V: ";
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\nDeque D: ";
    for (std::deque<int>::iterator i = d.begin(); i != d.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 3.8\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter elements of vector V: ";
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::vector<int> v((std::istream_iterator<int>(stream)),
                       std::istream_iterator<int>());
    if (!stream.eof() || v.empty()) {
      std::cout << "Invalid input\n";
      continue;
    }
    deleteOdd(&v);
    std::cout << "Result: ";
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 4.2\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::string file_name;
    std::cout << "Enter file name: ";
    std::getline(std::cin, file_name);
    if (!printOddNumbers(file_name)) {
      std::cout << "Invalid input\n";
      continue;
    }
    correct = true;
  }

  std::cout << "\nTask 5.9\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    int k;
    std::string extra;
    std::cout << "Enter number K: ";
    std::getline(std::cin, line);
    std::istringstream stream_k(line);
    if (!(stream_k >> k) || (stream_k >> extra) || k <= 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::cout << "Enter elements of vector V: ";
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::vector<int> v((std::istream_iterator<int>(stream)),
                       std::istream_iterator<int>());
    if (!stream.eof() || v.empty()) {
      std::cout << "Invalid input\n";
      continue;
    }
    duplicatePositive(&v, k);
    std::cout << "Result: ";
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 6.9\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter elements of list L1 (even count): ";
    std::getline(std::cin, line);
    std::istringstream stream1(line);
    std::list<int> list1((std::istream_iterator<int>(stream1)),
                         std::istream_iterator<int>());
    if (!stream1.eof() || list1.empty() || list1.size() % 2 != 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::cout << "Enter elements of list L2 (even count): ";
    std::getline(std::cin, line);
    std::istringstream stream2(line);
    std::list<int> list2((std::istream_iterator<int>(stream2)),
                         std::istream_iterator<int>());
    if (!stream2.eof() || list2.empty() || list2.size() % 2 != 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    duplicateHalf1(&list1);
    duplicateHalf2(&list2);
    std::cout << "List L1: ";
    for (std::list<int>::iterator i = list1.begin(); i != list1.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\nList L2: ";
    for (std::list<int>::iterator i = list2.begin(); i != list2.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 7.6\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter elements of list L: ";
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::list<int> l((std::istream_iterator<int>(stream)),
                     std::istream_iterator<int>());
    if (!stream.eof() || l.empty()) {
      std::cout << "Invalid input\n";
      continue;
    }
    positiveFirst(&l);
    std::cout << "Result: ";
    for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 8.2\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter words of list L (at least 2): ";
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::list<std::string> words((std::istream_iterator<std::string>(stream)),
                                 std::istream_iterator<std::string>());
    bool only_letters = true;
    for (std::list<std::string>::iterator i = words.begin();
         i != words.end(); ++i) {
      for (std::size_t j = 0; j < i->size(); j++) {
        if (!std::isalpha(static_cast<unsigned char>((*i)[j]))) {
          only_letters = false;
        }
      }
    }
    if (words.size() < 2 || !only_letters) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::deque<std::string> pairs = makePairs(words);
    std::cout << "Deque D: ";
    for (std::deque<std::string>::iterator i = pairs.begin();
         i != pairs.end(); ++i) {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    correct = true;
  }

  std::cout << "\nTask 9.1\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    int n;
    std::string extra;
    std::cout << "Enter number N: ";
    std::getline(std::cin, line);
    std::istringstream stream_n(line);
    if (!(stream_n >> n) || (stream_n >> extra) || n <= 0) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::cout << "Enter elements of vector V0: ";
    std::getline(std::cin, line);
    std::istringstream stream0(line);
    std::vector<int> v0((std::istream_iterator<int>(stream0)),
                        std::istream_iterator<int>());
    if (!stream0.eof() || v0.empty()) {
      std::cout << "Invalid input\n";
      continue;
    }
    int count = 0;
    bool all_correct = true;
    for (int i = 1; i <= n && all_correct; i++) {
      std::cout << "Enter elements of vector V" << i << ": ";
      std::getline(std::cin, line);
      std::istringstream stream(line);
      std::vector<int> current((std::istream_iterator<int>(stream)),
                               std::istream_iterator<int>());
      if (!stream.eof() || current.size() < v0.size()) {
        std::cout << "Invalid input\n";
        all_correct = false;
      } else if (isIncluded(v0, current)) {
        count++;
      }
    }
    if (!all_correct) {
      continue;
    }
    std::cout << "Vectors with all elements of V0: " << count << "\n";
    correct = true;
  }

  std::cout << "\nTask 10.1\n";
  correct = false;
  while (!correct) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << "Enter elements of vector V: ";
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::vector<int> v((std::istream_iterator<int>(stream)),
                       std::istream_iterator<int>());
    if (!stream.eof() || v.empty()) {
      std::cout << "Invalid input\n";
      continue;
    }
    std::map<int, int> repeats = countRepeats(v);
    std::cout << "Element and count:\n";
    for (std::map<int, int>::iterator i = repeats.begin();
         i != repeats.end(); ++i) {
      std::cout << i->first << " " << i->second << "\n";
    }
    correct = true;
  }

  return 0;
}
