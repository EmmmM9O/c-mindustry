#pragma once
#include "./Socket.hpp"

const char *Struct::TimeOut::what() const throw() { return "TimeOut!"; };
const char *Struct::HostErr::what() const throw() {
  return "Cann't get ip by the host:";
}

const char *Struct::ConnectEd::what() const throw() { return "Connected"; }
const char *Struct::UnConnect::what() const throw() { return "Un Connect"; }
const char *Struct::ConnectErr::what() const throw() { return "ConnectErr"; }
void Struct::Socket::read(java::nio::ByteBuffer *buf, int time) {
  auto f = std::async(
      std::launch::async, [this]() -> auto{ return dataSync(); });
  if (f.wait_for(std::chrono::seconds(time)) == std::future_status::ready) {
    auto b = f.get();
    std::cout << "Socket get A String ";
    for (auto i : b) {
      std::cout << (int)(byte)i << " ";
      buf->byteStream.push_back((byte)i);
    }
    std::cout << std::endl;
  } else {
    throw new TimeOut();
  }
}
std::string Struct::Socket::getIpByHost(std::string str) {
  auto a = gethostbyname(str.data());
  if (a == NULL) {
    throw HostErr();
  } else {
    std::string ip = "";
    for (int i = 0; a->h_addr_list[i]; i++) {
      ip = inet_ntoa(*(struct in_addr *)a->h_addr_list[i]);
    }
    return ip;
  }
}
Struct::Socket::Socket(domain dom, type t, int protocol) {
  id = socket((int)dom, (int)t, protocol);
  servaddr.sin_family = (int)dom;
}
template <typename T> void Struct::Socket::send(T arr, int length) {
  if (connectd) {
    int len;
    len = sendto(id, arr, length, 0, (struct sockaddr *)&servaddr,
                 sizeof(struct sockaddr));
    if (len < 0) {
      std::cout << "发送出错";
      perror("sendto");
      exit(1);
    }
  } else {
    throw UnConnect();
  }
}
void Struct::Socket::send(std::string str) {
  if (connectd) {
    int len;
    len = sendto(id, str.data(), str.length(), 0, (struct sockaddr *)&servaddr,
                 sizeof(struct sockaddr));
    if (len < 0) {
      std::cout << "发送出错";
      perror("sendto");
      exit(1);
    }
  } else {
    throw UnConnect();
  }
}
void Struct::Socket::connect(int port, std::string host) {
  if (!connectd) {
    std::smatch s;
    if (!std::regex_match(host, s, IPV4R)) {
      try {
        host = getIpByHost(host);
      } catch (HostErr &e) {
        throw e;
      }
    }
    servaddr.sin_port = htons(port);
    Chost = host;
    inet_pton(servaddr.sin_family, host.data(), &servaddr.sin_addr);
    bzero(&(servaddr.sin_zero), 8);
    if (::connect(id, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
      throw ConnectErr();
    }
    connectd = true;
  } else {
    throw ConnectEd();
  }
}
void Struct::Socket::close() {
  if (connectd) {
    ::close(id);
  } else {
    throw UnConnect();
  }
}

std::vector<char> Struct::Socket::dataSync() {
  if (connectd) {
    char recvbuf[BUFFER_SIZE];
    socklen_t len = sizeof(struct sockaddr);
    int lent;
    lent = recvfrom(id, recvbuf, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr,
                    &len);

    if (lent < 0) {
      perror("recvto");
      exit(1);
    }
    return std::vector<char>(recvbuf, recvbuf + lent);
  } else {
    // std::cout<<"还未连接";perror("no connect");exit(1);
    throw UnConnect();
  }
}
std::future<std::vector<char>> Struct::Socket::data() {
  if (connectd) {
    return std::async(std::launch::async, [this]() -> std::vector<char> {
      char recvbuf[BUFFER_SIZE];
      socklen_t len = sizeof(struct sockaddr);
      int lent;
      lent = recvfrom(this->id, recvbuf, BUFFER_SIZE, 0,
                      (struct sockaddr *)&this->servaddr, &len);
      if (lent < 0) {
        perror("recv");
        exit(1);
      }
      return std::vector<char>(recvbuf, recvbuf + lent);
    });
  } else {
    throw UnConnect();
  }
}
const std::regex Struct::Socket::IPV4R =
    std::regex("((25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(25[0-5]|2["
               "0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
