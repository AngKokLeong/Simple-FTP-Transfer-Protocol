package(default_visibility = ["//visibility:public"])
load("@rules_cc//cc:defs.bzl",  "cc_library")

cc_library(
	name = "FTP_CLIENT_DRIVER",
	srcs = ["ftp_client_driver.c"],
	hdrs = ["ftp_client_driver.h"],
	deps = [":FTP_CLIENT", ":FTP_CLIENT_HELPER_FUNCTION"],
)

cc_library(
	name = "FTP_CLIENT",
	srcs = ["ftp_client.c"],
	hdrs = ["ftp_client.h"],
	deps = [":FTP_CLIENT_HELPER_FUNCTION", "//PROTOCOL_COMMAND:COMMAND"],
)

cc_library(
	name = "FTP_CLIENT_HELPER_FUNCTION",
	srcs = ["ftp_client_helper_function.c"],
	hdrs = ["ftp_client_helper_function.h"],
)
