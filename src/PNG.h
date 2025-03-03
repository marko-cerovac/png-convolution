#include <fstream>

class PNG {
  public:

    PNG(std::ifstream& stream);
    PNG(const PNG& other);
    PNG(PNG&& other) noexcept;

    PNG& operator=(const PNG& other);
    PNG& operator=(PNG&& other) noexcept;

  private:
};
