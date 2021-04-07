package(default_visibility = ["//visibility:public"])
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
	name = "FTP_SERVER_DRIVER",
	srcs = ["ftp_server_driver.c"],
	hdrs = ["ftp_server_driver.h"],
	deps = [":FTP_SERVER", ":SERVER_HELPER_FUNCTION"],
)

cc_library(
	name = "FTP_SERVER",
	srcs = ["ftp_server.c"],
	hdrs = ["ftp_server.h"],
	deps = [":SERVER_HELPER_FUNCTION"],
)

cc_library(
	name = "SERVER_HELPER_FUNCTION",
	srcs = ["server_daemonize.c", "generate_random_port_number.c"],
	hdrs = ["server_helper_function.h"],
)
