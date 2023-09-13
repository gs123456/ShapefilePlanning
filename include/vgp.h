#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include<iostream>
#include "coorconv.h"

const static double EXPAND_DIST = 2.5;
const static double HEURISTIC_W = 1.0;

class VGPlanner
{
public:
    VGPlanner() {}
    VGPlanner(const double start_x, const double start_y,
              const double goal_x, const double goal_y,
              const std::vector<std::vector<std::pair<double, double>>> &obstacles)
        : start_x_(start_x), start_y_(start_y),
          goal_x_(goal_x), goal_y_(goal_y),
          obstacles_(obstacles)
    {
        for (auto obstacle : obstacles_)
        {
            std::pair<double, double> center(0., 0.);
            for (auto vertex : obstacle)
            {
                center.first += vertex.first;
                center.second += vertex.second;
            }
            center.first /= obstacle.size();
            center.second /= obstacle.size();
            obstacle_centers_.push_back(center);
        }
    }
    void point2point();
    void point2build();
    void set_start(const double start_x, const double start_y)
    {
        start_x_ = start_x;
        start_y_ = start_y;
    }
    void set_goal(const double goal_x, const double goal_y)
    {
        goal_x_ = goal_x;
        goal_y_ = goal_y;
    }
    void set_obstacles(const std::vector<std::vector<coorconv::UTMCoor>> &obstacles)
    {
        for(auto obstacle : obstacles)
        {
            std::vector<std::pair<double, double>> vertexs;
            for(auto vertex : obstacle)
            {
                vertexs.push_back({vertex.x, vertex.y});
            }
            obstacles_.push_back(vertexs);
        }
        for (auto obstacle : obstacles_)
        {
            std::pair<double, double> center(0., 0.);
            for (auto vertex : obstacle)
            {
                center.first += vertex.first;
                center.second += vertex.second;
            }
            center.first /= obstacle.size();
            center.second /= obstacle.size();
            obstacle_centers_.push_back(center);
        }
    }
    void set_obstacles(const std::vector<std::vector<std::pair<double, double>>> &obstacles)
    {
        obstacles_ = obstacles;
        for (auto obstacle : obstacles_)
        {
            std::pair<double, double> center(0., 0.);
            for (auto vertex : obstacle)
            {
                center.first += vertex.first;
                center.second += vertex.second;
            }
            center.first /= obstacle.size();
            center.second /= obstacle.size();
            obstacle_centers_.push_back(center);
        }
    }
    void get_result(std::vector<double> &path_x, std::vector<double> &path_y)
    {
        path_x = path_x_;
        path_y = path_y_;
    }
public:
    struct VGNode
    {
        double x_;
        double y_;
        double g_;
        double h_;
        std::string index_;
        VGNode *parent_;
        VGNode(double x, double y) : x_(x), y_(y), g_(0.0), h_(0.0), parent_(nullptr)
        {
            index_ = std::to_string(x_) + std::string("-") + std::to_string(y_);
        }
        double cost() { return g_ + HEURISTIC_W * h_; }
    };

private:
    // function
    void generate_nodes();
    void generate_edges();
    void backtrace();
    void dijkstra_search();
    // data
    double start_x_;
    double start_y_;
    double goal_x_;
    double goal_y_;
    std::vector<std::vector<std::pair<double, double>>> obstacles_;
    std::vector<std::pair<double, double>> obstacle_centers_;
    std::vector<double> path_x_;
    std::vector<double> path_y_;
    // vg utils
    std::unordered_map<std::string, VGNode> node_cache_;
    std::unordered_map<std::string, std::vector<std::string>> edge_cache_;
    // dijkstra utils
    std::unordered_map<std::string, VGNode *> open_set;
    std::unordered_map<std::string, VGNode *> close_set;
    struct cmp
    {
        bool operator()(const std::pair<std::string, double> &left,
                        const std::pair<std::string, double> &right) const
        {
            return left.second >= right.second;
        }
    };
    std::priority_queue<std::pair<std::string, double>,
                        std::vector<std::pair<std::string, double>>, cmp>
        open_pq;
};

// expand obstacle vertex
void calc_offset_xy(
    double px, double py,
    double x, double y,
    double nx, double ny,
    double &offset_x, double &offset_y)
{
    double p = std::atan2(y - py, x - px);
    double n = std::atan2(ny - y, nx - x);
    double offset = std::atan2(
                        std::sin(p) + std::sin(n),
                        std::cos(p) + std::cos(n)) +
                    M_PI_2;
    offset_x = x + EXPAND_DIST * std::cos(offset);
    offset_y = y + EXPAND_DIST * std::sin(offset);
}

void VGPlanner::generate_nodes()
{
    VGNode start(start_x_, start_y_);
    node_cache_.insert({start.index_, start});
    VGNode goal(goal_x_, goal_y_);
    node_cache_.insert({goal.index_, goal});
    for (auto obstacle : obstacles_)
    {
        for (int i = 0; i < obstacle.size(); ++i)
        {
            double node_x, node_y;
            calc_offset_xy(
                obstacle[(i - 1 + obstacle.size()) % obstacle.size()].first,
                obstacle[(i - 1 + obstacle.size()) % obstacle.size()].second,
                obstacle[i].first, obstacle[i].second,
                obstacle[(i + 1) % obstacle.size()].first,
                obstacle[(i + 1) % obstacle.size()].second,
                node_x, node_y);
            VGNode node(node_x, node_y);
            node_cache_.insert({node.index_, node});
        }
    }
}

int orientation(const double px, const double py,
                const double qx, const double qy,
                const double rx, const double ry)
{
    double val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (val < 0.)
        return 1;
    else if (val > 0.)
        return 2;
    else
        return 0;
}

bool on_segment(const double px, const double py,
                const double qx, const double qy,
                const double rx, const double ry)
{
    if ((qx <= std::max(px, rx) && (qx >= std::min(px, rx))) &&
        (qy <= std::max(py, ry) && (qy >= std::min(py, ry))))
        return true;
    return false;
}

bool check_seg_intersect(
    const double px1, const double py1,
    const double qx1, const double qy1,
    const double px2, const double py2,
    const double qx2, const double qy2)
{
    int o1 = orientation(px1, py1, qx1, qy1, px2, py2);
    int o2 = orientation(px1, py1, qx1, qy1, qx2, qy2);
    int o3 = orientation(px2, py2, qx2, qy2, px1, py1);
    int o4 = orientation(px2, py2, qx2, qy2, qx1, qy1);
    if ((o1 != o2) && (o3 != o4))
        return true;
    if ((o1 == 0) && on_segment(px1, py1, px2, py2, qx1, qy1))
        return true;
    if ((o2 == 0) && on_segment(px1, py1, qx2, qy2, qx1, qy1))
        return true;
    if ((o3 == 0) && on_segment(px2, py2, px1, py1, qx2, qy2))
        return true;
    if ((o4 == 0) && on_segment(px2, py2, qx1, qy1, qx2, qy2))
        return true;
    return false;
}

bool check_edge(
    const double pred_x, const double pred_y,
    const double next_x, const double next_y,
    const std::vector<std::pair<double, double>> &obstacle)
{
    for (int i = 0; i < obstacle.size(); ++i)
    {
        if (check_seg_intersect(
                pred_x, pred_y, next_x, next_y,
                obstacle[i].first, obstacle[i].second,
                obstacle[(i + 1) % obstacle.size()].first,
                obstacle[(i + 1) % obstacle.size()].second))
            return false;
    }
    return true;
}

void VGPlanner::generate_edges()
{
    for (auto iter1 : node_cache_)
    {
        std::vector<std::string> indexs;
        for (auto iter2 : node_cache_)
        {
            if (iter1.first == iter2.first)
                continue;
            if (std::sqrt(std::pow(iter1.second.x_ - iter2.second.x_, 2) +
                          std::pow(iter1.second.y_ - iter2.second.y_, 2)) < 1e-1)
                continue;
            bool valid = true;
            for (auto obstacle : obstacles_)
            {
                if (!check_edge(iter1.second.x_, iter1.second.y_,
                                iter2.second.x_, iter2.second.y_, obstacle))
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
                indexs.push_back(iter2.first);
        }
        edge_cache_.insert({iter1.first, indexs});
    }
}

void VGPlanner::backtrace()
{
    std::string goal_idx =
        std::to_string(goal_x_) + std::string("-") + std::to_string(goal_y_);
    VGNode *goal = &(node_cache_.find(goal_idx)->second);
    VGNode *curr = goal;
    while (curr->parent_)
    {
        path_x_.push_back(curr->x_);
        path_y_.push_back(curr->y_);
        curr = curr->parent_;
    }
    // add start
    path_x_.push_back(curr->x_);
    path_y_.push_back(curr->y_);
    std::reverse(path_x_.begin(), path_x_.end());
    std::reverse(path_y_.begin(), path_y_.end());
    std::cout << "---------------------------" << std::endl;
    std::cout << "Path total length: " << goal->cost() << std::endl;
    std::cout << "Node number: " << path_x_.size() << std::endl;
}

void VGPlanner::dijkstra_search()
{
    open_set.clear();
    close_set.clear();
    // initialize idx
    std::string start_idx =
        std::to_string(start_x_) + std::string("-") + std::to_string(start_y_);
    std::string goal_idx =
        std::to_string(goal_x_) + std::string("-") + std::to_string(goal_y_);
    // initialize node
    VGNode *start = &(node_cache_.find(start_idx)->second);
    start->g_ = 0.;
    start->h_ = std::sqrt(
        std::pow(start_x_ - goal_x_, 2) +
        std::pow(start_y_ - goal_y_, 2));
    // preparation
    open_set.insert({start->index_, start});
    open_pq.push({start->index_, start->cost()});
    while (!open_pq.empty())
    {
        // get current node
        std::string index = open_pq.top().first;
        VGNode *curr = open_set[index];
        open_pq.pop();
        close_set.insert({curr->index_, curr});
        // current node expansion
        auto iter = edge_cache_.find(curr->index_);
        if (iter == edge_cache_.end())
            continue;
        for (auto child_index : iter->second)
        {
            // if find the goal, exit!
            if (child_index == goal_idx)
            {
                VGNode *goal = &(node_cache_.find(child_index)->second);
                goal->g_ = curr->g_ + std::sqrt(
                                          std::pow(goal->x_ - curr->x_, 2) +
                                          std::pow(goal->y_ - curr->y_, 2));
                goal->h_ = 0.0;
                goal->parent_ = curr;
                backtrace();
                return;
            }
            // if in close set, skip!
            if (close_set.find(child_index) != close_set.end())
            {
                continue;
            }
            VGNode *child = &(node_cache_.find(child_index)->second);
            auto iter = open_set.find(child_index);
            // if already in open, check!
            if (iter != open_set.end())
            {
                double g = curr->g_ + std::sqrt(
                                          std::pow(child->x_ - curr->x_, 2) +
                                          std::pow(child->y_ - curr->y_, 2));
                if (g < child->g_)
                {
                    child->g_ = g;
                    child->parent_ = curr;
                    open_pq.push({child->index_, child->cost()});
                }
            }
            else // if not, add!
            {
                child->g_ = curr->g_ + std::sqrt(
                                           std::pow(child->x_ - curr->x_, 2) +
                                           std::pow(child->y_ - curr->y_, 2));
                child->h_ = std::sqrt(
                    std::pow(child->x_ - goal_x_, 2) +
                    std::pow(child->y_ - goal_y_, 2));
                child->parent_ = curr;
                open_pq.push({child->index_, child->cost()});
                open_set.insert({child->index_, child});
            }
        }
    }
}

void VGPlanner::point2point()
{
    // clear path
    path_x_.clear();
    path_y_.clear();
    // clear utils
    node_cache_.clear();
    edge_cache_.clear();
    // generate map
    std::cout<< 1.1<<std::endl;
    generate_nodes();
    std::cout<< 1.2<<std::endl;
    generate_edges();
    std::cout<< 1.3<<std::endl;
    // search path
    dijkstra_search();
}

void VGPlanner::point2build()
{
    // clear path
    path_x_.clear();
    path_y_.clear();
    // goal analysis
    double nearest_x, nearest_y;
    double min_dist = std::numeric_limits<double>::max();
    for (auto center : obstacle_centers_)
    {
        double dist = std::sqrt(
            std::pow(center.first - start_x_, 2) +
            std::pow(center.second - start_y_, 2));
        if(dist < min_dist)
        {
            min_dist = dist;
            nearest_x = center.first;
            nearest_y = center.second;
        }
    }
    path_x_.push_back(start_x_);
    path_x_.push_back(nearest_x);
    path_y_.push_back(start_y_);
    path_y_.push_back(nearest_y);
}