//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "SocketAsio.h"
#ifdef JOURNEY_USE_ASIO

namespace jrc
{
SocketAsio::SocketAsio() : resolver(ioservice), socket(ioservice)
{
}

SocketAsio::~SocketAsio()
{
    if (socket.is_open()) {
        error_code error;
        socket.close(error);
    }
}

bool SocketAsio::open(const char* address, const char* port)
{
    tcp::resolver::query query(address, port);
    tcp::resolver::iterator endpoint_iter = resolver.resolve(query);
    error_code error;
    asio::connect(socket, endpoint_iter, error);
    if (!error) {
        std::size_t result = socket.read_some(asio::buffer(buffer), error);
        return !error && result == HANDSHAKE_LEN;
    }
    return !error;
}

bool SocketAsio::close() noexcept
{
    error_code error;
    socket.shutdown(tcp::socket::shutdown_both, error);
    socket.close(error);
    return !error;
}

std::size_t SocketAsio::receive(bool* recvok)
{
    if (socket.available() > 0) {
        error_code error;
        std::size_t result = socket.read_some(asio::buffer(buffer), error);
        *recvok = !error;
        return result;
    }
    return 0;
}

const std::int8_t* SocketAsio::get_buffer() const
{
    return buffer;
}

bool SocketAsio::dispatch(const std::int8_t* bytes,
                          std::size_t length) noexcept
{
    error_code error;
    std::size_t result
        = asio::write(socket, asio::buffer(bytes, length), error);
    return !error && (result == length);
}
} // namespace jrc
#endif
