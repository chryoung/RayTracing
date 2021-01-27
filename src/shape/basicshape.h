#ifndef DE42175B_5A7D_4059_8113_AC1894425874
#define DE42175B_5A7D_4059_8113_AC1894425874

#include <cstdint>
#include <memory>

namespace RayTracer {
namespace Shape {
class BasicShape {
 public:
  virtual ~BasicShape() = default;
  std::uint64_t id() { return _id; }
  std::uint64_t id() const { return _id; }

 protected:
  explicit BasicShape(std::uint64_t id) : _id(id) {}

 private:
  std::uint64_t _id;
};

using BasicShapePtr = std::shared_ptr<BasicShape>;

inline bool operator==(const BasicShape& a, const BasicShape& b) { return a.id() == b.id(); }
}  // namespace Shape

}  // namespace RayTracer

#endif /* DE42175B_5A7D_4059_8113_AC1894425874 */
