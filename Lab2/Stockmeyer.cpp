#include "Stockmeyer.h"

void Stockmeyer::inputList(std::ifstream &input)
{
    std::vector<std::pair<int, int>> module_list;
    std::string Polish;

    getline(input, Polish);

    //Create the Pairs that are the width and the height
    while (!input.eof())
    {
        std::string str;
        getline(input, str);
        std::stringstream ss(str);
        int w, h;
        ss >> h;
        ss >> w;
        module_list.push_back(std::make_pair(w, h));
    }
    /*
    Store the Nodes into a temporary vector
    if the Node is a vertical cut it is a (1)
    if the Node is a horizontal cut it is a (2)
    if the Node is not a cut it is a (0) and will instead hold a pair<width, height>
    */
    while (Polish.length() > 0)
    {
        std::string token;
        if (Polish.length() > 1)
        {
            token = Polish.substr(0, 1);
            Polish = Polish.erase(0, 2);
        }
        else
        {
            token = Polish;
        }
        if (token.compare("V") == 0)
        {
            Node *root = new Node(1);
            node_list.push_back(root);
        }
        else if (token.compare("H") == 0)
        {
            Node *root = new Node(2);
            node_list.push_back(root);
        }
        else
        {
            std::stringstream module_index(token);
            int index;
            module_index >> index;
            Node *root = new Node(module_list.at(index - 1).first, module_list.at(index - 1).second);
            node_list.push_back(root);
        }
        //node_list.at(count).printNode();
        //count++;
    }
    /*
    Creates the tree from the post order traversal - left,right,root
    Only the vertical and horizontal cuts can be a root
    */
    bool visited[node_list.size()];
    for (int i = 0; i < node_list.size(); i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < node_list.size(); i++)
    {
        if (node_list.at(i)->cut_type != 0)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (visited[j] == false)
                {
                    node_list.at(i)->right = node_list.at(j);
                    //node_list.at(i)->printNode();
                    //std::cout << " right = " << j + 1;
                    //std::cout << std::endl;
                    visited[j] = true;
                    break;
                }
            }
            for (int j = i - 1; j > -1; j--)
            {
                if (visited[j] == false)
                {
                    node_list.at(i)->left = node_list.at(j);
                    //node_list.at(i)->printNode();
                    //std::cout << " left = " << j + 1;
                    //std::cout << std::endl;
                    visited[j] = true;
                    break;
                }
            }
        }
    }
    head = node_list.at(node_list.size() - 1);
}

int Stockmeyer::calculateHeight(Node *root)
{
    /*
    std::cout << "Visiting: ";
    root->printNode();
    std::cout << std::endl;
    */

    //base case & module dimension
    if (root->left == nullptr || root->right == nullptr)
    {
        return root->height;
    }
    //horizontal calculations
    else if (root->cut_type == 2)
    {
        return std::max(calculateHeight(root->left), calculateHeight(root->right));
    }
    //vertical calculations
    else if (root->cut_type == 1)
    {
        return calculateHeight(root->left) + calculateHeight(root->right);
    }
    else
    {
        return -1;
    }
}

int Stockmeyer::calculateWidth(Node *root)
{
    /*
    std::cout << "Visiting: ";
    root->printNode();
    std::cout << std::endl;
    */

    //base case & module dimension
    if (root->left == nullptr || root->right == nullptr)
    {
        return root->width;
    }
    //vertical calculations
    else if (root->cut_type == 1)
    {
        return std::max(calculateWidth(root->left), calculateWidth(root->right));
    }
    //horizontal calculations
    else if (root->cut_type == 2)
    {
        return calculateWidth(root->left) + calculateWidth(root->right);
    }
    else
    {
        return -1;
    }
}

void Stockmeyer::RotateNodes(Node *root)
{
    /*
    std::cout << "Visiting: ";
    root->printNode();
    std::cout << std::endl;
    */

    //base case & module dimension
    if (root->left == nullptr || root->right == nullptr)
    {
        return;
    }
    //vertical calculations
    else if (root->cut_type == 1)
    {
        RotateNodes(root->left);
        RotateNodes(root->right);
        for (int i = 0; i < root->left->calc_pairs.size(); i++)
        {
            for (int j = 0; j < root->right->calc_pairs.size(); j++)
            {
                std::pair<int, int> l = root->left->calc_pairs.at(i);
                std::pair<int, int> r = root->right->calc_pairs.at(j);
                // D = <l1 + r1, max(l2, r2)>
                std::pair<int, int> to_vector = std::make_pair(l.first + r.first, std::max(l.second, r.second));
                root->calc_pairs.push_back(to_vector);
            }
        }
        return;
    }
    //horizontal calculations
    else if (root->cut_type == 2)
    {
        RotateNodes(root->left);
        RotateNodes(root->right);
        for (int i = 0; i < root->left->calc_pairs.size(); i++)
        {
            for (int j = 0; j < root->right->calc_pairs.size(); j++)
            {
                std::pair<int, int> l = root->left->calc_pairs.at(i);
                std::pair<int, int> r = root->right->calc_pairs.at(j);
                // D = <max(l1, r1), l2 + r2>
                std::pair<int, int> to_vector = std::make_pair(std::max(l.first, r.first), l.second + r.second);
                root->calc_pairs.push_back(to_vector);
            }
        }
        return;
    }
    else
    {
        return;
    }
}

void Stockmeyer::printBestArea()
{
    int best_width;
    int best_height;
    int best_area;
    if (head->calc_pairs.size() > 0)
    {
        best_width = head->calc_pairs.at(0).first;
        best_height = head->calc_pairs.at(0).second;
        best_area = best_width * best_height;
    }
    for (int i = 0; i < head->calc_pairs.size(); i++)
    {
        int area = (head->calc_pairs.at(i).first) * (head->calc_pairs.at(i).second);
        if (area < best_area)
        {
            best_width = head->calc_pairs.at(i).first;
            best_height = head->calc_pairs.at(i).second;
            best_area = area;
        }
    }
    std::cout << "New Width:\t" << best_width << std::endl
              << "New Height\t" << best_height << std::endl
              << "Best Area\t" << best_area << std::endl;
}

void Stockmeyer::printNodesV()
{
    for (int i = 0; i < node_list.size(); i++)
    {
        std::cout << "List: (" << i + 1 << ") -- ";
        node_list.at(i)->printNode();
        std::cout << std::endl;
    }
}
void Stockmeyer::printNodesTreeCalc()
{
    for (int i = 0; i < node_list.size(); i++)
    {
        std::cout << "List: (" << i + 1 << ") -- ";
        node_list.at(i)->printNodeCalc();
        std::cout << std::endl;
    }
}