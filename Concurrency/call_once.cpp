#include <mutex>

class X
{
  private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;
    void init_connection()
    {
      connection = connection_manager::open(connection_details);
    }
  public:
    explicit X(connection_info const& info) : connection_details(info) {}
    void send_data(data_packet const& packet)
    {
      std::call_once(connection_init_flag, &X::init_connection, this);
      connection.send_data(packet);
    }
    data_packet receive_data()
    {
      std::call_once(connection_init_flag, &X::init_connection, this);
      return connection.receive_data();
    }
};
