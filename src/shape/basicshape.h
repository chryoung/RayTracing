#ifndef DE42175B_5A7D_4059_8113_AC1894425874
#define DE42175B_5A7D_4059_8113_AC1894425874

#include <cstdint>

namespace RayTracer {
namespace Shape {
class BasicShape {
 public:
  BasicShape(std::uint64_t id) : _id(id) {}
  virtual ~BasicShape() = default;
  std::uint64_t id() { return _id; }
  std::uint64_t id() const { return _id; }

 private:
  std::uint64_t _id;
};
}  // namespace Shape

}  // namespace RayTracer

#endif /* DE42175B_5A7D_4059_8113_AC1894425874 */
