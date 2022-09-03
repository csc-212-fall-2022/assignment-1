FROM mcr.microsoft.com/devcontainers/cpp:ubuntu
# Add the Kitware repo so we can get the latest cmake
# https://askubuntu.com/a/865294/1570674
ADD scripts/add_kiteware_repo.sh .
RUN apt update \
    && ./add_kiteware_repo.sh \
    && apt-get install -y clang-format clang-tidy cmake
