// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#pragma once

#include "stdint.h"

namespace rs
{
    namespace core
    {
        /**
         * @brief construct a unique id from a given set of characters.
         * @param X1        char 1
         * @param X2        char 2
         * @param X3        char 3
         * @param X4        char 4
         * @return int32_t  the unique id.
         */
        inline int32_t CONSTRUCT_UID(char X1,char X2,char X3,char X4)
        {
            return (((unsigned int)(X4)<<24)+((unsigned int)(X3)<<16)+((unsigned int)(X2)<<8)+(unsigned int)(X1));
        }

        /**
        * @enum Rotation
        *
        * Image rotation options.
        */
        enum class rotation
        {
            rotation_0_degree   = 0x0,   /** 0 Degree rotation */
            rotation_90_degree  = 90,    /** 90 degree clockwise rotation */
            rotation_180_degree = 180,   /** 180 degree clockwise rotation */
            rotation_270_degree = 270,   /** 270 degree clockwise rotation */
            rotation_invalid_value = -1
        };

        /**
         * @struct The device_info struct
         *
         * Decribes device details.
         */
        struct device_info
        {
            char                       name[224];    /** device name */
            char                       serial[32];   /** serial number */
            char                       firmware[32]; /** firmware version */
            rs::core::rotation         rotation;     /** how the camera device is physically mounted */
        };

        /**
         * @struct The sizeI32 struct
         */
        struct sizeI32
        {
            int32_t width, height;
        };

        /**
         * @enum The sample_flags enum
         */
        enum class sample_flags
        {
            none,     /** no special flags */
            external  /** sample generated from external device (platform camera \ external imu) */
        };

        /**
         * @enum The stream_type enum
         */
        enum class stream_type : int32_t
        {
            depth                            = 0,  /** Native stream of depth data produced by RealSense device                                             */
            color                            = 1,  /** Native stream of color data captured by RealSense device                                             */
            infrared                         = 2,  /** Native stream of infrared data captured by RealSense device                                          */
            infrared2                        = 3,  /** Native stream of infrared data captured from a second viewpoint by RealSense device                  */
            fisheye                          = 4,
            points                           = 5,  /** Synthetic stream containing point cloud data generated by deprojecting the depth image               */
            rectified_color                  = 6,  /** Synthetic stream containing undistorted color data with no extrinsic rotation from the depth stream  */
            color_aligned_to_depth           = 7,  /** Synthetic stream containing color data but sharing intrinsics of depth stream                        */
            infrared2_aligned_to_depth       = 8,  /** Synthetic stream containing second viewpoint infrared data but sharing intrinsics of depth stream    */
            depth_aligned_to_color           = 9,  /** Synthetic stream containing depth data but sharing intrinsics of color stream                        */
            depth_aligned_to_rectified_color = 10, /** Synthetic stream containing depth data but sharing intrinsics of rectified color stream              */
            depth_aligned_to_infrared2       = 11, /** Synthetic stream containing depth data but sharing intrinsics of second viewpoint infrared stream    */

            max                                    /** Max number of stream types, must be last                                                             */
        };

        /**
         * @enum The pixel_format enum
         */
        enum class pixel_format : int32_t
        {
            any         = 0,
            z16         = 1,  /** 16 bit linear depth values. The depth is meters is equal to depth scale * pixel value     */
            disparity16 = 2,  /** 16 bit linear disparity values. The depth in meters is equal to depth scale / pixel value */
            xyz32f      = 3,  /** 32 bit floating point 3D coordinates.                                                     */
            yuyv        = 4,
            rgb8        = 5,
            bgr8        = 6,
            rgba8       = 7,
            bgra8       = 8,
            y8          = 9,
            y16         = 10,
            raw8        = 11,
            raw10       = 12, /** Four 10-bit luminance values encoded into a 5-byte macropixel                             */
            raw16       = 13
        };

        /**
         * @enum The distortion_type enum
         */
        enum class distortion_type : int32_t
        {
            none                   = 0, /** Rectilinear images, no distortion compensation required                                                             */
            modified_brown_conrady = 1, /** Equivalent to Brown-Conrady distortion, except that tangential distortion is applied to radially distorted points   */
            inverse_brown_conrady  = 2, /** Equivalent to Brown-Conrady distortion, except undistorts image instead of distorting it                            */
            distortion_ftheta      = 3
        };

        /**
         * @struct The motion_device_intrinsics struct
         *
         * represents motion device intrinsics - scale, bias and variances
         */
        struct motion_device_intrinsics
        {
            float data[3][4];           /** Scale X        cross axis        cross axis      Bias X
                                            cross axis     Scale Y           cross axis      Bias Y
                                            cross axis     cross axis        Scale Z         Bias Z */
            float noise_variances[3];
            float bias_variances[3];
        };

        /**
         * @struct The intrinsics struct
         */
        struct intrinsics
        {
            int             width;     /** width of the image in pixels                                                                     */
            int             height;    /** height of the image in pixels                                                                    */
            float           ppx;       /** horizontal coordinate of the principal point of the image, as a pixel offset from the left edge  */
            float           ppy;       /** vertical coordinate of the principal point of the image, as a pixel offset from the top edge     */
            float           fx;        /** focal length of the image plane, as a multiple of pixel width                                    */
            float           fy;        /** focal length of the image plane, as a multiple of pixel height                                   */
            distortion_type model;     /** distortion model of the image                                                                    */
            float           coeffs[5]; /** distortion coefficients                                                                          */
        };

        /**
         * @struct The extrinsics struct
         */
        struct extrinsics
        {
            float rotation[9];    /** column-major 3x3 rotation matrix          */
            float translation[3]; /** 3 element translation vector, in meters   */
        };

        /**
        * @struct image_info
        *
        * Describes the image data detailed information.
        */
        struct image_info
        {
            int32_t                   width;              /** width of the image in pixels                                          */
            int32_t                   height;             /** height of the image in pixels                                         */
            pixel_format              format;             /** image pixel format                                                    */
            int32_t                   pitch;              /** number of bytes in a single image row of pixels, also known as stride */
        };

        /**
         * @struct The pointI32 struct
         */
        struct pointI32
        {
            int32_t x, y; /** representing a two dimensional point */
        };

        /**
         * @struct The pointF32 struct
         */
        struct pointF32
        {
            float x, y; /** representing a two dimensional point */
        };

        /**
         * @struct The point3dF32 struct
         */
        struct point3dF32
        {
            float x, y, z; /** representing a three-dimensional point */
        };

        /**
         * @struct The rect struct
         */
        struct rect
        {
            int x;
            int y;
            int width;
            int height;
        };

        /**
         * @struct The rectF32 struct
         */
        struct rectF32
        {
            float x;
            float y;
            float width;
            float height;
        };

        /**
         * @enum The motion_type enum
         */
        enum class motion_type : int32_t
        {
            accel       = 1,    /** accelerometer */
            gyro        = 2,    /** gyroscope     */

            max,
        };

        /**
         * @enum The timestamp_domain enum
         *
         * the source of the timestamp.
         */
        enum class timestamp_domain
        {
            camera,
            microcontroller
        };
    }
}
