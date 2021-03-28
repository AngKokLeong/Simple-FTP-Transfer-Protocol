package(default_visibility = ["//visibility:public"])
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
	name = "FTP_SERVER_DRIVER",
	srcs = ["ftp_server_driver.c"],
	deps = [":FTP_SERVER", ":SERVER_DAEMONIZE"],
)

cc_library(
	name = "FTP_SERVER",
	srcs = ["ftp_server.c"],
	hdrs = ["ftp_server.h"],
	deps = [":SERVER_DAEMONIZE"],
)

cc_library(
	name = "SERVER_DAEMONIZE",
	srcs = ["server_daemonize.c"],
)
