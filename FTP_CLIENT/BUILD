package(default_visibility = ["//visibility:public"])
load("@rules_cc//cc:defs.bzl",  "cc_library")

cc_library(
	name = "FTP_CLIENT_DRIVER",
	srcs = ["ftp_client_driver.c"],
	hdrs = ["ftp_client_driver.h"],
	deps = [":FTP_CLIENT"],
)

cc_library(
	name = "FTP_CLIENT",
	srcs = ["ftp_client.c"],
	hdrs = ["ftp_client.h"],
)
