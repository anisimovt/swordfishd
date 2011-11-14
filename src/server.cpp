/**
 * @file server.cpp
 * @author  Litvinova Alina
 */
//-------------------------------------------------------------------------------------------------
#include <boost/bind.hpp>
//-------------------------------------------------------------------------------------------------
#include "server.hpp"
//-------------------------------------------------------------------------------------------------
namespace wapstart {
  Server::Server(service_type &service, 
                 Storage      &storage,
                 port_type     port, 
                 size_type     workers): service_(service),
                                         storage_(storage),
                                         worker_(Worker::create(service, storage)),
                                         tpool_(workers),
                                         acceptor_(service, endpoint_type(
                                           boost::asio::ip::tcp::v4(), port))
  {
    acceptor_.async_accept(worker_->socket(), boost::bind(
      &Server::on_accept, this, boost::asio::placeholders::error)); 
  }
  //-----------------------------------------------------------------------------------------------
  void Server::on_accept(const error_code_type &error) 
  {
    if(!error) {
      tpool_.schedule(boost::bind(&Worker::_do, worker_)); 
      worker_ = Worker::create(service_, storage_);
      acceptor_.async_accept(worker_->socket(), boost::bind(
        &Server::on_accept, this, boost::asio::placeholders::error)); 
    }
  }
  //-----------------------------------------------------------------------------------------------
} // namespace wapstart
//-------------------------------------------------------------------------------------------------
