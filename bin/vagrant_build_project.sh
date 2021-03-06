#!/bin/sh

set -e

cd /vagrant
npm install
gem install bundler
rbenv rehash
bundle install

echo ""
echo ""
echo "Ready to go! Run the following to get started:"
echo ""
echo "$ vagrant ssh"
echo "$ cd /vagrant"
echo "$ grunt"
