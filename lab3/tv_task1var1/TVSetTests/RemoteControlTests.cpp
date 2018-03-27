#include "stdafx.h"
#include "../CTVSet.h"
#include "../RemoteControl.h"
#include <boost/optional.hpp>

// ����������� RemoteControl-a �������� � ������������ ���������,
// ����� ������������� �� �������� �� ��������������� ������ remote-������������
struct RemoteControlDependencies
{
	CTVSet tv;
	std::stringstream input;
	std::stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// ��������������� ������� ��� �������� ������ ������� command
	// ��� ��������� ��������� ����� ������ expectetChannel � expectedOutput
	void VerifyCommandHandling(const std::string& command, const boost::optional<int>& expectedChannel, const std::string& expectedOutput)
	{
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

// ������������� ����������
BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)
	// ����� ���������� ������� TurnOn
	BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}

	// ����� ��������� ���������, ������� �������
	BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("TurnOff", boost::none, "TV is turned off\n");
	}

	// ����� ������� ���������� � ����������
	BOOST_AUTO_TEST_CASE(can_print_tv_info)
	{
		// ��������� ��������� ������� Info, ��������� � ������������ ����������
		VerifyCommandHandling("Info", boost::none, "TV is turned off\n");

		// ��������� ��������� ������� Info � ����������� ����������
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	}

	// ����� ������� �������������� �����, ����� ��������� �������
	BOOST_AUTO_TEST_CASE(can_select_valid_channel_when_tv_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel 42", 42, "Channel selected\n");
	}

	// �� ����� ������� �����, ����� ��������� ��������
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_is_turned_off)
	{
		VerifyCommandHandling("SelectChannel 42", boost::none, "Can't select channel because TV is turned off\n");
		VerifyCommandHandling("SelectChannel 100", boost::none, "Can't select channel because TV is turned off\n");
	}

	// �� ����� ������� ���������������� �����, ����� ��������� �������
	BOOST_AUTO_TEST_CASE(cant_select_invalid_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
		VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
	}

	// ����� ������� �������������� ���������� �����, ����� ��������� �������
	BOOST_AUTO_TEST_CASE(can_select_valid_previous_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectPreviousChannel", 1, "Previous channel selected\n");
	}

	// �� ����� ������� ���������� �����, ����� ��������� ��������
	BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_tv_is_turned_off)
	{
		VerifyCommandHandling("SelectPreviousChannel", boost::none, "Can't select previous channel because TV is turned off\n");
	}

	// �� ����� ������� ���������������� ���������� �����, ����� ��������� �������
	BOOST_AUTO_TEST_CASE(cant_select_invalid_previous_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(100);
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectPreviousChannel", 1, "Previous channel selected\n");
	}
BOOST_AUTO_TEST_SUITE_END()
