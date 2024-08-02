/*
 * Copyright (C) 2021 by Autonomous Driving Group, Shanghai AI Laboratory
 * Limited. All rights reserved.
 * Yan Guohang <yanguohang@pjlab.org.cn>
 * Ouyang Jinhua <ouyangjinhua@pjlab.org.cn>
 */
#pragma once

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "../../json.hpp"

using json = nlohmann::json;

void LoadIntrinsic(const std::string &filename, Eigen::Matrix3d &K,std::vector<double> &dist) {

  std::ifstream in(filename, std::ios::binary);

  // std::ifstream in;
  // in.open(filename);
  if (!in.is_open()) {
    std::cout << "Error Opening " << filename << std::endl;
    return;
  }

    json root;
    try {
        in >> root;
    } catch (json::exception &e) {
        std::cout << e.what()<< std::endl;
        in.close();
        return ;
    }
    in.close();

    auto intri = root["center_camera-intrinsic"]["param"]["cam_K"]["data"];
    auto d = root["center_camera-intrinsic"]["param"]["cam_dist"]["data"];
    int dist_col = root["center_camera-intrinsic"]["param"]["cam_dist"]["cols"];

    K << intri[0][0], intri[0][1], intri[0][2],
        intri[1][0], intri[1][1], intri[1][2],
        intri[2][0], intri[2][1], intri[2][2];
    dist.clear();
    for (int i = 0; i < dist_col; i++) {
      dist.push_back(d[0][i]);
    }
}
