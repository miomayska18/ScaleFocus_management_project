USE [ProjectManagement]
GO
/****** Object:  Database [ProjectManagement]    Script Date: 7/6/2021 2:40:01 PM ******/
CREATE DATABASE [ProjectManagement]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'ProjectManagement', FILENAME = N'C:\Users\miomayska18\ProjectManagement.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'ProjectManagement_log', FILENAME = N'C:\Users\miomayska18\ProjectManagement_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [ProjectManagement].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [ProjectManagement] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [ProjectManagement] SET ARITHABORT OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [ProjectManagement] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [ProjectManagement] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [ProjectManagement] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [ProjectManagement] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [ProjectManagement] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [ProjectManagement] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [ProjectManagement] SET  DISABLE_BROKER 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [ProjectManagement] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [ProjectManagement] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [ProjectManagement] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [ProjectManagement] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [ProjectManagement] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [ProjectManagement] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [ProjectManagement] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [ProjectManagement] SET  MULTI_USER 
GO
ALTER DATABASE [ProjectManagement] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [ProjectManagement] SET DB_CHAINING OFF 
GO
ALTER DATABASE [ProjectManagement] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [ProjectManagement] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [ProjectManagement] SET DELAYED_DURABILITY = DISABLED 
GO
USE [ProjectManagement]
GO
/****** Object:  Table [dbo].[Log]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Log](
	[Id] [int] NOT NULL,
	[UserId] [int] NOT NULL,
	[TimeSpent] [decimal](4, 2) NOT NULL,
	[Date] [datetime] NOT NULL,
	[TaskId] [int] NOT NULL,
 CONSTRAINT [PK_Log] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Project]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Project](
	[Id] [int] NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](50) NOT NULL,
	[OwnerId] [int] NOT NULL,
	[DateCreation] [datetime] NOT NULL,
	[IdCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
	[TaskId] [int] NOT NULL,
 CONSTRAINT [PK_Project] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ProjectsTeams]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ProjectsTeams](
	[ProjectId] [int] NOT NULL,
	[TeamsId] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Task]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Task](
	[Id] [int] NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](50) NOT NULL,
	[ProjectId] [int] NOT NULL,
	[Status] [bit] NOT NULL,
 CONSTRAINT [PK_Task] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Team]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Team](
	[Id] [int] NOT NULL,
	[TeamName] [nvarchar](50) NOT NULL,
	[Members] [nvarchar](50) NOT NULL,
	[ProjectId] [int] NOT NULL,
	[DateCreation] [datetime] NOT NULL,
	[IdCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
 CONSTRAINT [PK_Team] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[User]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[User](
	[Id] [int] NOT NULL,
	[UserName] [nvarchar](50) NOT NULL,
	[Password] [varbinary](50) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
	[IsAdmin] [bit] NOT NULL,
 CONSTRAINT [PK_User] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/6/2021 2:40:01 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[UserId] [int] NOT NULL,
	[TeamId] [int] NOT NULL
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Log]  WITH CHECK ADD  CONSTRAINT [FK_Log_Task] FOREIGN KEY([TaskId])
REFERENCES [dbo].[Task] ([Id])
GO
ALTER TABLE [dbo].[Log] CHECK CONSTRAINT [FK_Log_Task]
GO
ALTER TABLE [dbo].[Project]  WITH CHECK ADD  CONSTRAINT [FK_Project_Task] FOREIGN KEY([TaskId])
REFERENCES [dbo].[Task] ([Id])
GO
ALTER TABLE [dbo].[Project] CHECK CONSTRAINT [FK_Project_Task]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Project] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Project] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Project]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Team] FOREIGN KEY([TeamsId])
REFERENCES [dbo].[Team] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Team]
GO
ALTER TABLE [dbo].[User]  WITH CHECK ADD  CONSTRAINT [FK_IdLastChange_Id] FOREIGN KEY([IdLastChange])
REFERENCES [dbo].[User] ([Id])
GO
ALTER TABLE [dbo].[User] CHECK CONSTRAINT [FK_IdLastChange_Id]
GO
ALTER TABLE [dbo].[User]  WITH CHECK ADD  CONSTRAINT [FK_IdOfCreator_Id] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[User] ([Id])
GO
ALTER TABLE [dbo].[User] CHECK CONSTRAINT [FK_IdOfCreator_Id]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Team] FOREIGN KEY([TeamId])
REFERENCES [dbo].[Team] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Team]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_User] FOREIGN KEY([UserId])
REFERENCES [dbo].[User] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_User]
GO
USE [master]
GO
ALTER DATABASE [ProjectManagement] SET  READ_WRITE 
GO
