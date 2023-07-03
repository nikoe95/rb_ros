#include <cstdio>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interfaces/srv/communicator_request.hpp"

using namespace rclcpp;

class Communicator : public rclcpp::Node
{
  public:
    Communicator() : Node("rb_communicator_node")
    {

      RCLCPP_INFO(get_logger(), "Communicator node started");
      communicator_service = create_service<custom_interfaces::srv::CommunicatorRequest>("rb_communicator_node/communicator_server", std::bind(&Communicator::new_message, this, std::placeholders::_1, std::placeholders::_2));
   }

    rclcpp::Service<custom_interfaces::srv::CommunicatorRequest>::SharedPtr communicator_service;

    void new_message(const std::shared_ptr<custom_interfaces::srv::CommunicatorRequest::Request> request,
                     std::shared_ptr<custom_interfaces::srv::CommunicatorRequest::Response> response)
                     {
                        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request : %s", request->in_com.c_str());
                        response->out_com = "HelloWorld";
                     }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Communicator>());
  rclcpp::shutdown();

  return 0;
}
