/*
 * Copyright (C) 2021 by Autonomous Driving Group, Shanghai AI Laboratory
 * Limited. All rights reserved.
 * Yan Guohang <yanguohang@pjlab.org.cn>
 * Ouyang Jinhua <ouyangjinhua@pjlab.org.cn>
 */
#pragma once

#include <fstream>
#include <iostream>
#include "../../json.hpp"
#include <stdio.h>
#include <string>

using json = nlohmann::json;

void LoadExtrinsic(const std::string &filename, Eigen::Matrix4d &extrinsic) {

  std::ifstream in(filename, std::ios::binary);
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

    auto data = root["top_center_lidar-to-center_camera-extrinsic"]["param"]["sensor_calib"]["data"];
    extrinsic << data[0][0], data[0][1],
        data[0][2], data[0][3], data[1][0],
        data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2],
        data[2][3], data[3][0], data[3][1],
        data[3][2], data[3][3];
}