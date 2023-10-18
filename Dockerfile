FROM alpine:latest
RUN apk --no-cache add \
    cmake \
    clang \
    libxml2-dev \
    linux-headers \
    make \
    musl-dev \
    ncurses-dev \
    valgrind
ENV CC=clang
RUN mkdir -p app
COPY . app/
WORKDIR app
RUN make fclean && make
