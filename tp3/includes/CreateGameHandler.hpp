/* 
 * File:   CreateGameHandler.hpp
 * Author: xaqq
 *
 * Created on November 22, 2013, 12:13 AM
 */

#ifndef CREATEGAMEHANDLER_HPP
#define	CREATEGAMEHANDLER_HPP

#include "APacketHandler.hpp"
#include "CMSGCreateGame.hpp"

class CreateGameHandler : public APacketHandler
{
public:
  CreateGameHandler();
  CreateGameHandler(const CreateGameHandler& orig) = delete;
  virtual ~CreateGameHandler();
  
  bool handle(CMSGCreateGame *p) override;
private:

};

#endif	/* CREATEGAMEHANDLER_HPP */

