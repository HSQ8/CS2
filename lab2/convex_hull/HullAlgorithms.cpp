/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include <algorithm>
#include "HullAlgorithms.hpp"
#include <cmath>

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * TODO: Implement this function.
 */



void swapnum(std::vector<double> &list, int indexA, int indexB);
void swapPointer(vector<Tuple*> &points, int a1, int a2);
int pivotNum(std::vector<double>& v, int low, int high, vector<Tuple*> &points){
    int i = low - 1;
    int pivot = high;
    for(int j = low; j < high; ++j){
        if (v.at(j) < v.at(pivot)){
            i++;
            swapnum(v,i,j);
            swapPointer(points, i, j);
        }
    }
    swapnum(v, i + 1, high);
    swapPointer(points, i + 1, high);
    return i+1;
}

void quicksort_inplace(std::vector<double> &list, int left, int right, vector<Tuple*> &points)
{
    if (left < right){
        int pivot = pivotNum(list, left,right, points);
        quicksort_inplace(list,pivot + 1, right, points);
        quicksort_inplace(list,left, pivot - 1, points);
    }
}
void swapPointer(vector<Tuple*> &points, int a1, int a2){
    Tuple * tempPtr = points.at(a1);
    points.at(a1) = points.at(a2);
    points.at(a2) = tempPtr;
}
void swapnum(std::vector<double> &list, int indexA, int indexB){
    double temp = list.at(indexA);
    list.at(indexA) = list.at(indexB);
    list.at(indexB) = temp;
}

void sort(vector<Tuple*> &points, vector<double> &angles)
{
    quicksort_inplace(angles, 0, angles.size() - 1, points);
    
}


double getPointAngle(Tuple* point1, Tuple* point2){
    int dx = point2->x - point1->x;
    int dy = point2->y - point1->y;
    if(point1->x == point2->x){
        if (dy < 0){
            return 180.0;
        }else{
            return 0.0;
        }
    }else if(point1->y == point2->y){
        if(dx < 0){
            return 270.0;
        }else{
            return 90.0;
        }
    }else if(dx > 0 && dy > 0){
        return 90 - std::atan2(dy,dx) * 180 / M_PI;

    }else if(dx < 0 && dy > 0){
        return 180 - std::atan2(dy,dx) * 180 / M_PI + 270;
    }else if(dx > 0 && dy < 0){
        return 90 - std::atan2(dy,dx) * 180 / M_PI;
        
    }else if(dx < 0 && dy < 0){
        return 90 - std::atan2(dy,dx) * 180 / M_PI;
    }
    return 0.0;
}

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    Tuple* start = points.at(0);
    for(auto i: points){
        if (i->x < start->x){
            start = i;
        }
    }

    Tuple* current = start;
    Tuple* next = points[1];
    app->add_to_hull(start);
    double prevangle = 0;
    
    while(next != start){
        //std::cout << "here"<<endl;
       double currentangle = 360.0;   
       for(auto i:points){

        if(i != current){
            double newangle = getPointAngle(current, i);
            if(currentangle > newangle && newangle > prevangle){

                currentangle = newangle;
                next = i;
                    //cout << "ifloop" << endl;
            }
        }
    }
    prevangle = currentangle;
    app->add_to_hull(next);
    current = next;
}
}


double getTripletAngle(Tuple* point3,Tuple* vertex,Tuple* point1){
    double x1 = point1->x - vertex->x;
    double y1 = point1->y - vertex->y;
    double x2 = point3->x - vertex->x;
    double y2 = point3->y - vertex->y;
    double dot = x1*x2 + y1*y2;
    double det = x1*y2 - y1*x2;
    double angle = atan2(det,dot) * 180 / M_PI;
    if(angle < 0)
        angle += 360;
    return angle;
}
 /**
 * TODO: Implement this function.
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    Tuple* start = points.at(0);
    for(auto i: points){
        if (i->x < start->x){
            start = i;
        }
    }
    

    Tuple* origin = new Tuple(0,0);
    std::vector<double> angles;
    for(auto i:points){
        angles.push_back(getPointAngle(start, i) - getPointAngle(start, origin));
    }

    sort(points, angles);

    std::vector<Tuple*> mypoints;
    for(auto i: points){
        mypoints.push_back(i);
    }

    auto it = std::find(mypoints.begin(),mypoints.end(),start);
    if (it != mypoints.end()) {
      mypoints.erase(it);
  }
  
  mypoints.push_back(start);
  std::vector<Tuple*> path;
  path.push_back(start);
  path.push_back(mypoints.at(0));
  mypoints.erase(mypoints.begin());
  path.push_back(mypoints.at(0));
  mypoints.erase(mypoints.begin());
  double angle;
  for (auto i: mypoints){
    path.push_back(i);
    angle = getTripletAngle(path.at(path.size() - 1), path.at(path.size() - 2),path.at(path.size() - 3));
    cout << path.size() << endl;
        std::cout << "whileout" << angle << endl;
    while(angle >= 180){
        cout << path.size() << endl;
        std::cout << "while" << angle << endl;
        path.erase(path.end() - 2);
        angle = getTripletAngle(path.at(path.size() - 1), path.at(path.size() - 2),path.at(path.size() - 3));
        
    }
    
}
for (auto i: path){
    app->add_to_hull(i);
}

}