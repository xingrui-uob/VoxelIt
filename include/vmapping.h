#ifndef VMAPPING_INCLUDE_VMAPPING_H
#define VMAPPING_INCLUDE_VMAPPING_H

#include <Eigen/Core>
#include <memory>
#include <opencv2/opencv.hpp>
#include <sophus/se3.hpp>

namespace vmap
{
class VoxelMapping
{
public:
    VoxelMapping(int w, int h, const Eigen::Matrix3f& K);
    ~VoxelMapping();

    void reset();
    void CreateMap(int numEntries, int numVoxels, float voxelSize);
    void FuseDepth(cv::cuda::GpuMat depth, const Eigen::Matrix4f& camToWorld);
    void FuseDepthAndImage(cv::Mat rgb, cv::Mat depth, const Eigen::Matrix4f& camToWorld);
    void RenderScene(cv::cuda::GpuMat& vmap, const Eigen::Matrix4f& camToWorld);
    int Polygonize(float*& verts_out, float*& norms_out);
    std::vector<Eigen::Vector3f> GetSurfacePoints();
    void ReadSDF(const std::vector<Eigen::Vector3f>& points,
                 std::vector<Eigen::Vector3f>& neighbours,
                 std::vector<float>& sdf, std::vector<bool>& validity);

protected:
    struct VoxelizationImpl;
    std::unique_ptr<VoxelizationImpl> impl;
};

} // namespace vmap

#endif