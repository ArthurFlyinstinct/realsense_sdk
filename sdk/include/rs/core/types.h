// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#pragma once

#include "stdint.h"

namespace rs
{
    namespace core
    {
        __inline int32_t CONSTRUCT_UID(char X1,char X2,char X3,char X4)
        {
            return (((unsigned int)(X4)<<24)+((unsigned int)(X3)<<16)+((unsigned int)(X2)<<8)+(unsigned int)(X1));
        }

        /**
        @enum Rotation
        Image rotation options.
        */
        enum class rotation
        {
            rotation_0_degree   = 0x0,   // 0 Degree rotation
            rotation_90_degree  = 90,    // 90 degree clockwise rotation
            rotation_180_degree = 180,   // 180 degree clockwise rotation
            rotation_270_degree = 270,   // 270 degree clockwise rotation
            rotation_invalid_value = -1
        };

        /**
         @brief The device_info struct
         Decribes device details.
         */
        struct device_info
        {
            char                       name[224];    // device name
            char                       serial[32];   // serial number
            char                       firmware[32]; // firmware version
            rs::core::rotation         rotation;     // how the camera device is physically mounted
        };

        struct sizeI32
        {
            int32_t width, height;
        };

        enum class sample_flags
        {
            none,
            external  // sample generated from external device (platform camera \ external imu)
        };

        enum class stream_type : int32_t
        {
            depth                            = 0,  // Native stream of depth data produced by RealSense device
            color                            = 1,  // Native stream of color data captured by RealSense device
            infrared                         = 2,  // Native stream of infrared data captured by RealSense device
            infrared2                        = 3,  // Native stream of infrared data captured from a second viewpoint by RealSense device
            fisheye                          = 4,
            rectified_color                  = 5,  // Synthetic stream containing undistorted color data with no extrinsic rotation from the depth stream
            max                                    // Max number of stream types, must be last
        };

        enum class pixel_format : int32_t
        {
            any         = 0,
            z16         = 1,  // 16 bit linear depth values. The depth is meters is equal to depth scale * pixel value
            disparity16 = 2,  // 16 bit linear disparity values. The depth in meters is equal to depth scale / pixel value
            xyz32f      = 3,  // 32 bit floating point 3D coordinates.
            yuyv        = 4,
            rgb8        = 5,
            bgr8        = 6,
            rgba8       = 7,
            bgra8       = 8,
            y8          = 9,
            y16         = 10,
            raw8        = 11,
            raw10       = 12,  // Four 10-bit luminance values encoded into a 5-byte macropixel
            raw16       = 13
        };

        enum class preset_type : int32_t
        {
            default_config = 0  // default device options values
        };

        enum class distortion_type : int32_t
        {
            none                   = 0, // Rectilinear images, no distortion compensation required
            modified_brown_conrady = 1, // Equivalent to Brown-Conrady distortion, except that tangential distortion is applied to radially distorted points
            inverse_brown_conrady  = 2, // Equivalent to Brown-Conrady distortion, except undistorts image instead of distorting it
            distortion_ftheta      = 3
        };

        /* represents motion device intrinsics - scale, bias and variances */
        struct motion_device_intrinsics
        {
            /* Scale X        cross axis        cross axis      Bias X */
            /* cross axis     Scale Y           cross axis      Bias Y */
            /* cross axis     cross axis        Scale Z         Bias Z */
            float data[3][4];

            float noise_variances[3];
            float bias_variances[3];
        };

        struct intrinsics
        {
            int             width;     // width of the image in pixels
            int             height;    // height of the image in pixels
            float           ppx;       // horizontal coordinate of the principal point of the image, as a pixel offset from the left edge
            float           ppy;       // vertical coordinate of the principal point of the image, as a pixel offset from the top edge
            float           fx;        // focal length of the image plane, as a multiple of pixel width
            float           fy;        // focal length of the image plane, as a multiple of pixel height
            distortion_type model;     // distortion model of the image
            float           coeffs[5]; // distortion coefficients
        };

        struct extrinsics
        {
            float rotation[9];    // column-major 3x3 rotation matrix
            float translation[3]; // 3 element translation vector, in meters
        };

        /**
        @struct image_info
        Describes the image data detailed information.
        */
        struct image_info
        {
            int32_t                   width;              /* width of the image in pixels */
            int32_t                   height;             /* height of the image in pixels */
            pixel_format              format;             /* image pixel format */
            int32_t                   pitch;              /* number of bytes in a single image row of pixels, also known as stride*/
        };

        struct pointI32
        {
            int32_t x, y; //representing a two dimensional point
        };

        struct pointF32
        {
            float x, y; //representing a two dimensional point
        };

        struct point3dF32
        {
            float x, y, z; //representing a three-dimensional point
        };

        struct rect
        {
            int x;
            int y;
            int width;
            int height;
        };

        struct rectF32
        {
            float x;
            float y;
            float width;
            float height;
        };

        enum class motion_type : int32_t
        {
            accel       = 1,
            gyro        = 2,

            max,
        };

        enum class timestamp_domain
        {
            camera,
            microcontroller
        };
    }
}
