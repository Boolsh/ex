#include <iostream>
#include "Binary_Tree.h"
#include "Trie_Tree.h"
#include <Windows.h>
#include <stack>
#include <queue>
//#include "Counter.h"
//лекция 12.11 перегрузка операторов


//ариант 3
//удаление рекурсивно яруса листьев в бинарном дереве
void task4_1(btree::ptrNODE& node)
{
    if (node)
    {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else
        {
            task4_1(node->left);
            task4_1(node->right);
        }

    }
}

void del_notrec(btree::ptrNODE& root)
{
    if (root)
    {
        std::stack<btree::ptrNODE> stack;
        std::stack<btree::ptrNODE> pre_stack;
        stack.push(root);
        pre_stack.push(nullptr);

        while (!stack.empty())
        {
            btree::ptrNODE current = stack.top();
            btree::ptrNODE parent = pre_stack.top();
            stack.pop();
            pre_stack.pop();

            if (current->left == nullptr && current->right == nullptr)
            {
                if (parent != nullptr)
                {
                    if (parent->left == current)
                    {
                        parent->left = nullptr;
                    }
                    else
                    {
                        parent->right = nullptr;
                    }
                }
                else
                {
                    root = nullptr;
                }
                delete current;
            }
            else
            {
                if (current->right != nullptr)
                {
                    stack.push(current->right);
                    pre_stack.push(current);
                }
                if (current->left != nullptr)
                {
                    stack.push(current->left);
                    pre_stack.push(current);
                }
            }
        }
    }
}
//ариант 4
//добавление рекурсивно яруса листьев в бинарном дереве
void task3_1(btree::ptrNODE& node)
{
    if (node)
    {
        task3_1(node->left);
        task3_1(node->right);
        if (node->left == nullptr || node->right == nullptr) {
            {
                if (node->left == nullptr)
                    node->left = new btree::NODE(0);
                if (node->right == nullptr)
                    node->right = new btree::NODE(0);
            }
        }
    }
}

void add_notrec(btree::ptrNODE& root)
{
    if (root)
    {
        std::stack<btree::ptrNODE> stack;
        stack.push(root);
        while (!stack.empty())
        {
            btree::ptrNODE curr = stack.top();
            stack.pop();

            if (curr->left == nullptr)
                curr->left = new btree::NODE(0);
            else
                stack.push(curr->left);
            if (curr->right == nullptr)
                curr->right = new btree::NODE(0);
            else
                stack.push(curr->right);
        }
    }

}

//сумма элеметов до чётного
int task3_2(btree::ptrNODE root)
{
    int sum = 0;
    if (root)
    {
        std::stack<btree::ptrNODE> stack;
        stack.push(root);
        while (!stack.empty()) {
            btree::ptrNODE current = stack.top();
            stack.pop();

            sum += current->info;

            if (current->info % 2 != 0) {
                if (current->right) {
                    stack.push(current->right);
                }
                if (current->left) {
                    stack.push(current->left);
                }
            }

        }
    }
    return sum;
}

int sum1_rec(btree::ptrNODE root, int& sum)
{
    if (root)
    {
        sum += root->info;
        if (root->left == nullptr && root->right == nullptr || root->info % 2 == 0)
            return sum;
        if (root->left)
        {
            sum1_rec(root->left, sum);
        }
        if (root->right)
        {
            sum1_rec(root->right, sum);
        }
    }
}
int task4_2(btree::ptrNODE root, int level) {
    int sum = 0;

    if (root && level >= 0)
    {
        std::queue<btree::ptrNODE> nodeQueue; // Очередь для узлов
        std::queue<int> levelQueue;           // Очередь для уровней
        nodeQueue.push(root);
        levelQueue.push(0);                   // Начинаем с уровня 0
        while (!nodeQueue.empty()) {
            btree::ptrNODE current = nodeQueue.front();
            int currentLevel = levelQueue.front();
            nodeQueue.pop();
            levelQueue.pop();
            // Если текущий уровень меньше или равен заданному
            if (currentLevel <= level) {
                sum += current->info; // Добавляем значение узла к сумме

                // Добавляем дочерние узлы в очередь с увеличением уровня
                if (current->left) {
                    nodeQueue.push(current->left);
                    levelQueue.push(currentLevel + 1);
                }
                if (current->right) {
                    nodeQueue.push(current->right);
                    levelQueue.push(currentLevel + 1);
                }
            }
        }
    }
    return sum;
}


int sum2_rec(btree::ptrNODE root, int level, int& sum, int currlvl) {
    if (root && level >= 0)
    {
        sum += root->info;
        if (currlvl == level || root->left == nullptr && root->right == nullptr)
            return sum;
        if (root->left)
        {
            sum2_rec(root->left, level, sum, currlvl + 1);
        }
        if (root->right)
        {
            sum2_rec(root->right, level, sum, currlvl + 1);
        }
    }
}

// сумма листьев
int sum_leafs_rec(btree::ptrNODE& root, int& sum)
{
    if (root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return sum += root->info;
        sum_leafs_rec(root->left, sum);
        sum_leafs_rec(root->right, sum);
    }
}

int sum_leafs_notrec(btree::ptrNODE& root)
{
    int sum{};
    if (root)
    {
        std::stack<btree::ptrNODE> stack;
        stack.push(root);
        while (!stack.empty())
        {
            btree::ptrNODE curr = stack.top();
            stack.pop();
            if (curr->left == nullptr && curr->right == nullptr)
                sum += curr->info;
            if (curr->left)
                stack.push(curr->left);
            if (curr->right)
                stack.push(curr->right);

        }
    }
    return sum;
}

//количество отрицат элементов
void otrits_rec(btree::ptrNODE root, int& count)
{
    if (root)
    {
        if (root->info < 0)
            ++count;
        otrits_rec(root->left, count);
        otrits_rec(root->right, count);
    }
}

int otrits_rec2(btree::ptrNODE root)
{
    int cnt{};
    if (root)
        cnt = (root->info < 0 ? 1 : 0) + otrits_rec2(root->left) + otrits_rec2(root->right);
    return cnt;
}

int otrits_notrec(btree::ptrNODE root)
{
    int cnt{};
    if (root)
    {
        std::stack<btree::ptrNODE> stack;
        stack.push(root);
        while (!stack.empty())
        {
            btree::ptrNODE curr = stack.top();
            stack.pop();
            if (curr->info < 0)
                ++cnt;
            if (curr->left)
                stack.push(curr->left);
            if (curr->right)
                stack.push(curr->right);
        }
    }
    return cnt;
}

int count_even_q(btree::ptrNODE root)
{
    std::queue<btree::ptrNODE>q;
    btree::ptrNODE t{};
    q.push(root);
    int res{};
    while (!q.empty())
    {
        t = q.front(); q.pop();
        res += t->info % 2 == 1 ? 1 : 0;
        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
    return res;
}

int count_even_st(btree::ptrNODE root)
{
    int res{};
    btree::ptrNODE t{ root };
    std::stack<btree::ptrNODE>st;
    while (t)
    {
        res += t->info % 2 == 1 ? 1 : 0;
        if (t->left)
        {
            if (t->right)
                st.push(t->right);
            t = t->left;
        }
        else
        {
            if (t->right)
                t = t->right;
            else
            {
                if (st.empty())
                    t = nullptr;
                else
                {
                    t = st.top();
                    st.pop();
                }
            }
        }
    }
    return res;
}


//btree::ptrNODE task_1(int n, int level) {
//    btree::ptrNODE result{};
//    if (level <= n) {
//        result = new btree::NODE(level);
//        result->left = task_1(n, level + 1);
//        result->right = task_1(n, level + 1);
//    }
//}

btree::TInfo task_2(btree::ptrNODE root, int level, int n) {
    btree::TInfo res{};
    if (root && level <= n)
        res = (level == n ? root->info : 0) + task_2(root->left, level + 1, n) + task_2(root->right, level + 1, n);
    return res;
}

auto maxL = [](btree::TInfo x, btree::TInfo y) {return (x > y ? x : y); };
int task_3(btree::ptrNODE root) {
    int result{ -1 };
    if (root) {
        result = maxL(task_3(root->left), task_3(root->right)) + 1;
    }
    return result;
}

auto is_leaf = [](btree::ptrNODE ptr) {return !ptr->left && !ptr->right; };
int task_4(btree::ptrNODE root) {
    std::queue<btree::ptrNODE> q;
    int res{};
    btree::ptrNODE t{ root };
    q.push(t);
    while (!q.empty()) {
        t = q.front(); q.pop();
        if (is_leaf(t) && t->info % 2 == 0)
            ++res;
        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
    return res;
}

btree::ptrNODE copy(btree::ptrNODE root, int& cnt_child) {
    btree::ptrNODE result{};
    int cnt_child_left{}, cnt_child_right{};
    if (root) {
        result = new btree::NODE(0);
        result->left = copy(root->left, cnt_child_left);
        result->right = copy(root->right, cnt_child_right);
        cnt_child = result->info + 1;
    }
    return result;
}
void task_5(btree::BTREE& tree, btree::BTREE& copy_tree) {
    int cnt_child{};
    copy_tree.set_root(copy(tree.get_root(), cnt_child));
}

void max_rec(btree::ptrNODE root, btree::TInfo& res)
{
    if (root)
    {
        if (abs(root->info) > abs(res))
            res = root->info;
        max_rec(root->left, res);
        max_rec(root->right, res);
    }
}

btree::TInfo max_stack(btree::ptrNODE root) // в глубину
{
    btree::TInfo max{};
    std::stack<btree::ptrNODE> stack;
    while (root)
    {
        max = abs(root->info) > abs(max) ? root->info : max;
        if (root->left)
        {
            if (root->right)
                stack.push(root->right);
            root = root->left;
        }
        else
        {
            if (root->right)
                root = root->right;
            else
            {
                if (stack.empty())
                    root = nullptr;
                else
                {
                    root = stack.top();
                    stack.pop();
                }
            }
        }
    }
    return max;
}


btree::TInfo max_queue(btree::ptrNODE root) // в ширину
{
    btree::TInfo max{};
    if (root)
    {
        std::queue<btree::ptrNODE> q;
        q.push(root);
        while (!q.empty())
        {
            btree::ptrNODE curr = q.front();
            q.pop();
            if (abs(curr->info) > abs(max))
                max = curr->info;
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }
    return max;
}

// самый левый лист
btree::ptrNODE find_left_leaf(btree::ptrNODE root)
{
    if (root)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            return root;
        }
        if (root->left)
            find_left_leaf(root->left);
        else if (root->right)
            find_left_leaf(root->right);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////ТРАЙ ДЕРЕВЬЯ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// сократить слова на последнюю букву
void del_last_letter(ttree::TTREE& tree, ttree::ptrNODE& root)
{
    if (root)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (root->ptrs[i])
            {
                if (root->ptrs[i]->eow)
                {
                    delete root->ptrs[i];
                    root->ptrs[i] = nullptr;
                    root->eow = true;
                }
                else
                    del_last_letter(tree, root->ptrs[i]);
            }
        }
    }
}

// дублировать слова на последнюю букву
void copy_last_letter(ttree::TTREE& tree, ttree::ptrNODE& root)
{
    if (root)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (root->ptrs[i])
            {
                if (root->ptrs[i]->eow)
                {
                    root->ptrs[i]->ptrs[i] = new ttree::NODE();
                    root->ptrs[i]->eow = false;
                    root->ptrs[i]->ptrs[i]->eow = true;

                }
                else
                    copy_last_letter(tree, root->ptrs[i]);
            }
        }
    }
}
bool is_gl(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}
//4. Дано Trie-дерево. Посчитать количество слов, которые содержат определенное количество гласных.
int cnt_words1(ttree::ptrNODE& root, int gl, int cnt_vowels = 0) {
    int count = 0;

    if (root) {
        for (int i = 0; i < 26; ++i) {
            if (root->ptrs[i]) {
                int new_cnt_vowels = cnt_vowels + (is_gl('a' + i) ? 1 : 0);
                if (root->ptrs[i]->eow) {
                    if (new_cnt_vowels == gl) {
                        count++;
                    }
                }
                count += cnt_words1(root->ptrs[i], gl, new_cnt_vowels);
            }
        }
    }
    return count;
}
// копировать
ttree::ptrNODE copyn(ttree::ptrNODE root) {
    if (!root) {
        return nullptr;
    }

    ttree::ptrNODE result = new ttree::NODE();
    result->eow = root->eow;

    for (int i = 0; i < 26; ++i) {
        if (root->ptrs[i]) {
            result->ptrs[i] = copyn(root->ptrs[i]);
        }
    }

    return result;
}
ttree::TTREE copy(ttree::ptrNODE root) {
    ttree::TTREE result;
    result.set_root(copyn(root));
    return result;
}

// 18. Дано Trie-дерево. Распечатать слова, начинающиеся с заданной подстроки.

bool is_in(std::string word, std::string sub)
{
    bool fl{ true };
    for (int i{}; i < sub.length() && fl; ++i)
    {
        if (word[i] != sub[i])
            fl = false;
    }
    return fl;
    //return word.find(sub) != std::string::npos;
}
void print_words_start(ttree::ptrNODE t, std::string sub, std::string word)
{
    if (t->eow && is_in(word, sub))
        std::cout << word << std::endl;
    for (int i = 0; i < 26; i++)
        if (t->ptrs[i])
            print_words_start(t->ptrs[i], sub, word + char(i + 'a'));
}
////удаляет всё что начинается на подстроку word
//void task_3_first(ttree::TTREE& tree, ttree::ptrNODE& root, std::string word, int lvl)
//{
//    if (root) {
//        if (lvl == word.length())
//            tree.clear(root);
//        else {
//            task_3_first(tree, root->ptrs[word[lvl] - 'a'], word, lvl + 1);
//            if (tree.all_prts_empty(root) && !root->eow) {
//                delete root;
//                root = nullptr;
//            }
//
//        }
//    }
//}
//================================================================
//Counter operator+(const Counter& c1, const Counter& c2)
//{
//    return Counter{ c1.get_value() + c2.get_value() };
//}
//
//Counter operator-(const Counter& c1, const Counter& c2)
//{
//    return Counter{ c1.get_value() - c2.get_value() };
//}

class Grafix
{
private:
    int x, y;
    int* c;
public:
    Grafix()
    {
        x = y = 0;
        c = nullptr;
    }
    Grafix(int x, int y, int* c = nullptr)
    {
        this->x = x;
        this->y = y;
        this->c = c;
    }
    void destroy()
    {
        x = y = 0;
        delete[] c;
        c = nullptr;
    }
    // Конструктор копирования
    Grafix(const Grafix& other) : x(other.x), y(other.y) {
        std::cout << "copy\n";
        if (other.c) {
            c = new int[*other.c]; 
            for (int i = 0; i < *other.c; ++i) { 
                c[i] = other.c[i];
            }
        }
        else {
            c = nullptr;
        }
    }
    // Конструктор перемещения
    Grafix(Grafix&& other) noexcept : x(other.x), y(other.y), c(other.c) {
        std::cout << "move\n";
        other.x = 0;
        other.y = 0;
        other.c = nullptr; 
    }
    Grafix& operator=(const Grafix& other)
    {
        if (this != &other)
        {
            destroy();
            x = other.x;
            y = other.y;
            if (other.c) {
                c = new int[*other.c];
                for (int i = 0; i < *other.c; ++i) {
                    c[i] = other.c[i];
                }
            }
            else {
                c = nullptr;
            }
        }
        return *this;
    }
    Grafix& operator=(Grafix&&other )
    {
        if (this != &other)
        {
            destroy();
            x = other.x;
            y = other.y;
            if (other.c) {
                c = new int[*other.c];
                for (int i = 0; i < *other.c; ++i) {
                    c[i] = other.c[i];
                }
            }
            else {
                c = nullptr;
            }
            other.destroy();
        }
        return *this;
    }
    Grafix operator+(const Grafix& other) const
    {
        return Grafix{ x + other.x, y + other.y, c };
    }

};







int main()
{
    SetConsoleOutputCP(1251);
    //ttree::TTREE tree("text.txt");
    //ttree::ptrNODE node = tree.get_root();
    //std::cout << "Исходник:" << std::endl;
    //tree.print("");
    //int cnt{ 0 };
    //std::cout << cnt_words1(node, 2, cnt) << '\n';
    //Counter c1(10);
    //Counter c2(12);
    ///*std::cout << (c1 + c2).get_value();*/
    //c1 = c2;
    //std::cout << c1.get_value() << ' ' << c2.get_value();
    Grafix g1(1, 10);
    Grafix g2(std::move(g1));


    //std::cout << "\nНОВЫЙ:" << std::endl;
    //tree.print("");
    /*btree::ptrNODE node = tree.get_root();
    int sum{};
    otrits_rec(node, sum);
    std::cout << "\nРезультат:" << otrits_rec2(node) << std::endl;*/

}
